#pragma once

#include <MetaNN/data/facilities/shape.h>

#include <MetaNN/policies/policy_operations.h>
#include <MetaNN/policies/policy_selector.h>
#include <MetaNN/policies/change_policy.h>
#include <MetaNN/facilities/var_type_dict.h>
#include <MetaNN/layers/facilities/policies.h>

#include <MetaNN/data/data.h>
#include <MetaNN/data/dynamic.h>

#include <MetaNN/data/batch/array.h>
#include <MetaNN/data/batch/duplicate.h>

#include <MetaNN/operators/abs.h>
#include <MetaNN/operators/add.h>
#include <MetaNN/operators/collapse.h>
#include <MetaNN/operators/conv.h>
#include <MetaNN/operators/divide.h>
#include <MetaNN/operators/dot.h>
#include <MetaNN/operators/multiply.h>
#include <MetaNN/operators/interpolate.h>
#include <MetaNN/operators/negative_log_likelihood.h>
#include <MetaNN/operators/negative_log_likelihood_derivative.h>
#include <MetaNN/operators/sigmoid.h>
#include <MetaNN/operators/sigmoid_grad.h>
#include <MetaNN/operators/sign.h>
#include <MetaNN/operators/softmax.h>
#include <MetaNN/operators/softmax_grad.h>
#include <MetaNN/operators/substract.h>
#include <MetaNN/operators/tanh.h>
#include <MetaNN/operators/tanh_grad.h>
#include <MetaNN/operators/transpose.h>

#include <MetaNN/data_copy/data_copy.h>

#include <MetaNN/policies/inject_policy.h>
#include <MetaNN/layers/elementary/abs_layer.h>
#include <MetaNN/layers/elementary/add_layer.h>
#include <MetaNN/layers/elementary/bias_layer.h>
#include <MetaNN/layers/elementary/element_mul_layer.h>
#include <MetaNN/layers/elementary/interpolate_layer.h>
#include <MetaNN/layers/elementary/sigmoid_layer.h>
#include <MetaNN/layers/elementary/softmax_layer.h>
#include <MetaNN/layers/elementary/tanh_layer.h>
#include <MetaNN/layers/elementary/weight_layer.h>

#include <MetaNN/layers/compose/linear_layer.h>
#include <MetaNN/layers/compose/single_layer.h>

#include <MetaNN/layers/recurrent/recurrent_layer.h>

#include <MetaNN/layers/cost/nll_loss_layer.h>

#include <MetaNN/model/param_initializer/constant_filler.h>
#include <MetaNN/model/param_initializer/gaussian_filler.h>
#include <MetaNN/model/param_initializer/uniform_filler.h>
#include <MetaNN/model/param_initializer/var_scale_filler.h>
#include <MetaNN/model/param_initializer/param_initializer.h>

#include <MetaNN/facilities/cont_metafuns/sequential.h>