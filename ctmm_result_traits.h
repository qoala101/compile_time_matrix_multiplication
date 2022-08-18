#ifndef CTMM_RESULT_TRAITS_H_
#define CTMM_RESULT_TRAITS_H_

#include "ctmm_concepts.h"  // IWYU pragma: keep

namespace ctmm {
/**
 * @brief Result matrix size and value type.
 */
template <unsigned NumRows, unsigned NumCols, typename ResultType>
struct ResultTraits {
  static constexpr unsigned kNumRows = NumRows;
  static constexpr unsigned kNumCols = NumCols;
  using ValueType = ResultType;
};

/**
 * @brief Produces the object of type describing the result
 * of the matrix expression evaluation.
 *
 * @tparam Expression Type of matrix expression to be evaluated.
 * @param input_values 2D containers with values readable
 * by [unsigned][unsigned]. Amount must be equal to the amount of matrices
 * used to define the expression. Used only to determine the type of the result,
 * so could be empty.
 */
template <MatExpression Expression>
[[nodiscard]] constexpr auto GetResultTraits(
    const MatValues auto &...input_values) {
  using ResultType =
      decltype(Expression::template EvaluateCell<0, 0,
                                                 sizeof...(input_values) - 1>(
          input_values...));
  return ResultTraits<Expression::kNumRows, Expression::kNumCols, ResultType>{};
}

/**
 * @copydoc GetResultTraits<MatExpression>
 * @param expression Defines the type of the evaluated expression.
 */
[[nodiscard]] constexpr auto GetResultTraits(
    const MatExpression auto &expression,
    const MatValues auto &...input_values) {
  return GetResultTraits<std::decay_t<decltype(expression)>>(input_values...);
}
}  // namespace ctmm

#endif  // CTMM_RESULT_TRAITS_H_
