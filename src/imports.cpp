#include "dplyr.h"

namespace rlang {

// *INDENT-OFF*
struct rlang_api_ptrs_t {
  SEXP (*eval_tidy)(SEXP expr, SEXP data, SEXP env);
  SEXP (*as_data_pronoun)(SEXP x);
  SEXP (*new_data_mask)(SEXP bottom, SEXP top);
  SEXP (*str_as_symbol)(SEXP str);

  rlang_api_ptrs_t() {
    eval_tidy       = (SEXP (*)(SEXP, SEXP, SEXP)) R_GetCCallable("rlang", "rlang_eval_tidy");
    as_data_pronoun = (SEXP (*)(SEXP))             R_GetCCallable("rlang", "rlang_as_data_pronoun");
    new_data_mask   = (SEXP (*)(SEXP, SEXP))       R_GetCCallable("rlang", "rlang_new_data_mask_3.0.0");
    str_as_symbol   = (SEXP (*)(SEXP))             R_GetCCallable("rlang", "rlang_str_as_symbol");
  }
};
// *INDENT-ON*

const rlang_api_ptrs_t& rlang_api() {
  static rlang_api_ptrs_t ptrs;
  return ptrs;
}

SEXP eval_tidy(SEXP expr, SEXP data, SEXP env) {
  return rlang_api().eval_tidy(expr, data, env);
}

SEXP as_data_pronoun(SEXP x) {
  return rlang_api().as_data_pronoun(x);
}

SEXP new_data_mask(SEXP bottom, SEXP top) {
  return rlang_api().new_data_mask(bottom, top);
}

SEXP str_as_symbol(SEXP str) {
  return rlang_api().str_as_symbol(str);
}

}

namespace vctrs {

// *INDENT-OFF*
struct vctrs_api_ptrs_t {
  bool (*vec_is_vector)(SEXP x);
  R_len_t (*short_vec_size)(SEXP x);
  SEXP (*short_vec_recycle)(SEXP, R_len_t);
  SEXP (*compact_seq)(R_len_t, R_len_t, bool);
  SEXP (*vec_chop)(SEXP, SEXP);

  vctrs_api_ptrs_t() {
    vec_is_vector     = (bool (*)(SEXP))                   R_GetCCallable("vctrs", "vec_is_vector");
    short_vec_size    = (R_len_t (*)(SEXP))                R_GetCCallable("vctrs", "short_vec_size");
    short_vec_recycle = (SEXP (*)(SEXP, R_len_t))          R_GetCCallable("vctrs", "short_vec_recycle");

    compact_seq       = (SEXP (*)(R_len_t, R_len_t, bool)) R_GetCCallable("vctrs", "exp_short_compact_seq");
    vec_chop          = (SEXP (*)(SEXP, SEXP))             R_GetCCallable("vctrs", "exp_vec_chop");
  }
};
// *INDENT-ON*

const vctrs_api_ptrs_t& vctrs_api() {
  static vctrs_api_ptrs_t ptrs;
  return ptrs;
}

bool vec_is_vector(SEXP x) {
  return vctrs_api().vec_is_vector(x);
}

R_len_t short_vec_size(SEXP x) {
  return vctrs_api().short_vec_size(x);
}

SEXP short_vec_recycle(SEXP x, R_len_t n) {
  return vctrs_api().short_vec_recycle(x, n);
}

SEXP compact_seq(R_len_t start, R_len_t size, bool increasing) {
  return vctrs_api().compact_seq(start, size, increasing);
}

SEXP vec_chop(SEXP x, SEXP indices) {
  return vctrs_api().vec_chop(x, indices);
}

}
