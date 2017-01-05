#include <string.h>
#include "nif_util.h"

ERL_NIF_TERM
make_atom(ErlNifEnv *env, const char *atom_name)
{
  ERL_NIF_TERM atom;
  if (enif_make_existing_atom(env, atom_name, &atom, ERL_NIF_LATIN1))
    return atom;

  return enif_make_atom(env, atom_name);
}

ERL_NIF_TERM
make_ok_tuple(ErlNifEnv *env, ERL_NIF_TERM value)
{
  return enif_make_tuple2(env, make_atom(env, "ok"), value);
}

ERL_NIF_TERM
make_error_tuple(ErlNifEnv *env, const char *reason)
{
  return enif_make_tuple2(env, make_atom(env, "error"), make_atom(env, reason));
}

ERL_NIF_TERM
make_string_len(ErlNifEnv *env, ERL_NIF_TERM term)
{
  ErlNifBinary bin;
  char * string;
  if (!enif_inspect_iolist_as_binary(env, term, &bin))
    return enif_make_badarg(env);

  string = bin.data;
  return enif_make_string_len(env, string, bin.size, ERL_NIF_LATIN1);
}
