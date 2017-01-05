#ifndef _NIF_UTIL_H_
#define _NIF_UTIL_H_

#include <erl_nif.h>

ERL_NIF_TERM
make_atom(ErlNifEnv *env, const char *atom_name);

ERL_NIF_TERM
make_ok_tuple(ErlNifEnv *env, ERL_NIF_TERM value);

ERL_NIF_TERM
make_error_tuple(ErlNifEnv *env, const char *reason);

ERL_NIF_TERM
make_string_len(ErlNifEnv *env, ERL_NIF_TERM term);

#endif
