#pragma once

#include <MetaNN/layers/facilities/common_io.h>
#include <MetaNN/layers/facilities/policies.h>
#include <MetaNN/layers/facilities/traits.h>
#include <MetaNN/policies/policy_operations.h>
#include <MetaNN/policies/policy_selector.h>
#include <stack>
namespace MetaNN
{
    template <typename TInputs, typename TPolicies>
    class AddLayer;
    
    template <>
    struct LayerInputPortSet_<AddLayer<void, void>>
    {
        using type = LayerPortSet<struct LeftOperand, struct RightOperand>;
    };
    
    template <typename TInputs, typename TPolicies>
    class AddLayer
    {
        static_assert(IsPolicyContainer<TPolicies>);
        using CurLayerPolicy = PlainPolicy<TPolicies>;

    public:
        static constexpr bool IsFeedbackOutput = PolicySelect<GradPolicy, CurLayerPolicy>::IsFeedbackOutput;
        static constexpr bool IsUpdate = false;
        
        using InputPortSet = LayerInputPortSet<AddLayer>;
        using OutputPortSet = LayerOutputPortSet<AddLayer>;
        using InputMap = TInputs;
        
    private:
        using TLeftOperandFP = typename InputMap::template Find<LeftOperand>;
        using TRightOperandFP = typename InputMap::template Find<RightOperand>;
        
    public:
        AddLayer(std::string name)
            : m_name(std::move(name))
        {}

        template <typename TIn>
        auto FeedForward(TIn&& p_in)
        {
            const auto& input1 = LayerTraits::PickItemFromCont<InputMap, LeftOperand>(std::forward<TIn>(p_in));
            const auto& input2 = LayerTraits::PickItemFromCont<InputMap, RightOperand>(std::forward<TIn>(p_in));
            auto proShape = LayerTraits::ShapePromote(input1, input2);
            auto res = DuplicateOrKeep(input1, proShape) + DuplicateOrKeep(input2, proShape);
            
            if constexpr (IsFeedbackOutput)
            {
                m_inputShapeChecker1.PushDataShape(input1);
                m_inputShapeChecker2.PushDataShape(input2);
                m_input1.push(std::move(input1));
                m_input2.push(std::move(input2));
            }

            return LayerOutputCont<AddLayer>().template Set<LayerOutput>(std::move(res));
        }
        
        template <typename TGrad>
        auto FeedBackward(TGrad&& p_grad)
        {
            if constexpr (!IsFeedbackOutput || RemConstRef<TGrad>::template IsValueEmpty<LayerOutput>)
            {
                if constexpr (IsFeedbackOutput)
                {
                    LayerTraits::PopoutFromStack(m_input1, m_input2, m_inputShapeChecker1, m_inputShapeChecker2);
                }
                return LayerInputCont<AddLayer>();
            }
            else
            {
                if ((m_input1.empty()) || (m_input2.empty()))
                {
                    throw std::runtime_error("Cannot feed back in AddLayer");
                }
                
                auto input1 = m_input1.top(); auto input2 = m_input2.top();
                auto grad = std::forward<TGrad>(p_grad).template Get<LayerOutput>();

                auto res1 = CollapseOrOmit(grad, std::move(input1));
                auto res2 = CollapseOrOmit(grad, std::move(input2));
                m_inputShapeChecker1.CheckDataShape(res1);
                m_inputShapeChecker2.CheckDataShape(res2);
                
                LayerTraits::PopoutFromStack(m_input1, m_input2, m_inputShapeChecker1, m_inputShapeChecker2);
                return LayerInputCont<AddLayer>().template Set<LeftOperand>(std::move(res1))
                                                 .template Set<RightOperand>(std::move(res2));
            }
        }
        
        void NeutralInvariant() const
        {
            if constexpr(IsFeedbackOutput)
            {
                LayerTraits::CheckStackEmpty(m_input1, m_input2, m_inputShapeChecker1, m_inputShapeChecker2);
            }
        }
    private:
        std::string m_name;

        LayerTraits::LayerInternalBuf<TLeftOperandFP,  IsFeedbackOutput> m_input1;
        LayerTraits::LayerInternalBuf<TRightOperandFP, IsFeedbackOutput> m_input2;
        
        LayerTraits::ShapeChecker<TLeftOperandFP,  IsFeedbackOutput> m_inputShapeChecker1;
        LayerTraits::ShapeChecker<TRightOperandFP, IsFeedbackOutput> m_inputShapeChecker2;
    };
}