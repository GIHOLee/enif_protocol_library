#include <erl_nif.h>
#include <string.h>
#include <dlfcn.h>

#include "nif_util.h"
#include "zjj_dll.h"

#define SO_FILE_NAME "libsplitairconditioning_ethnet_dsj_zhygzdn.so"
#define NIF_MODULE splitairconditioning_ethnet_dsj_zhygzdn_nif

#define METERID_LEN (12+1)
#define MAXINUM_SIZE (1024+1)
#define FUN_NAME_LEN (256+1)
#define BCD_LEN (3+1)

#define DATA_PACK "data_pack"
#define DATA_RESULT "data_result"

#define INPUT_RECORD_NAME "input_rd"
#define OUTPUT_RECORD_NAME "output_rd"

static ERL_NIF_TERM exec_func_nif(ErlNifEnv *env, int argc, const ERL_NIF_TERM argv[])
{
  int arity;
  const ERL_NIF_TERM *array_input;
  const ERL_NIF_TERM *array_output;

  INPUT_STRU in;
  OUTPUT_STRU out;

  void *handle;
  int (*func)(INPUT_STRU *, OUTPUT_STRU *);
  char fun_name[FUN_NAME_LEN];

  handle = dlopen(SO_FILE_NAME, RTLD_NOW | RTLD_GLOBAL);

  if (NULL == handle)
    {
      char *error_dl = dlerror();
      return make_error_tuple(env, error_dl);
    }

  if (argc != 3)
    return enif_make_badarg(env);

  if (!enif_get_string(env, argv[0], fun_name, FUN_NAME_LEN, ERL_NIF_LATIN1))
    return make_error_tuple(env, "invalid_function_name");

  if (!enif_get_tuple(env, argv[1], &arity, &array_input) || arity != 10)
    return make_error_tuple(env, "invalid_input_tuple");

  if (!enif_get_tuple(env, argv[2], &arity, &array_output) || arity != 8)
    return make_error_tuple(env, "invalid_output_tuple");

  char meterADDR[METERID_LEN] = {'0'};
  char collector2[METERID_LEN];
  char collector1[METERID_LEN];
  char info[MAXINUM_SIZE];
  int info_datalen = 0;
  char route1[METERID_LEN];
  char route2[METERID_LEN];
  char isBCD[BCD_LEN];
  unsigned char subSEQ = 0;

  if (!enif_is_atom(env, array_input[0]))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_input[1], meterADDR, METERID_LEN, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_input[2], collector2, METERID_LEN, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_input[3], collector1, METERID_LEN, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_input[4], info, MAXINUM_SIZE, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_int(env, array_input[5], &info_datalen))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_input[6], route1, METERID_LEN, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_input[7], route2, METERID_LEN, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_input[8], isBCD, 4, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_uint(env, array_input[9], (unsigned *)&subSEQ))
    return enif_make_badarg(env);

  in.meterADDR = meterADDR;
  in.collector2 = collector2;
  in.collector1 = collector1;
  in.info = info;
  in.info_datalen = info_datalen;
  in.route1 = route1;
  in.route2 = route2;
  in.isBCD = isBCD;
  in.subSEQ = subSEQ;

  char data[MAXINUM_SIZE];
  char frame[MAXINUM_SIZE];
  char error[MAXINUM_SIZE];
  int data_len = 0;
  int frame_len = 0;
  int err_len = 0;

  if (!enif_is_atom(env, array_output[0]))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_output[1], data, MAXINUM_SIZE, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_output[2], frame, MAXINUM_SIZE, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_string(env, array_output[3], error, MAXINUM_SIZE, ERL_NIF_LATIN1))
    return enif_make_badarg(env);

  if (!enif_get_int(env, array_output[4], &data_len))
    return enif_make_badarg(env);

  if (!enif_get_int(env, array_output[5], &frame_len))
    return enif_make_badarg(env);

  if (!enif_get_int(env, array_output[6], &err_len))
    return enif_make_badarg(env);

  if (!enif_is_number(env, array_output[7]))
    return enif_make_badarg(env);

  out.data = data;
  out.frame = frame;
  out.error = error;
  out.data_len = data_len;
  out.frame_len = frame_len;
  out.err_len = err_len;

  func = dlsym(handle, fun_name);
  int func_result = func(&in, &out);
  close(handle);

  ERL_NIF_TERM input_record_name_term, meterADDR_term, collector2_term, collector1_term, info_term, info_datalen_term, route1_term, route2_term, isBCD_term, subSEQ_term;
  input_record_name_term = make_atom(env, INPUT_RECORD_NAME);
  meterADDR_term = enif_make_string_len(env, in.meterADDR, strlen(in.meterADDR), ERL_NIF_LATIN1);
  collector2_term = enif_make_string_len(env, in.collector2, strlen(in.collector2), ERL_NIF_LATIN1);
  collector1_term = enif_make_string_len(env, in.collector1, strlen(in.collector1), ERL_NIF_LATIN1);
  info_term = enif_make_string_len(env, in.info, in.info_datalen, ERL_NIF_LATIN1);
  info_datalen_term = enif_make_int(env, in.info_datalen);
  route1_term = enif_make_string_len(env, in.route1, strlen(route1), ERL_NIF_LATIN1);
  route2_term = enif_make_string_len(env, in.route2, strlen(route2), ERL_NIF_LATIN1);
  isBCD_term = enif_make_string_len(env, in.isBCD, strlen(isBCD), ERL_NIF_LATIN1);
  subSEQ_term = enif_make_int(env, in.subSEQ);
  ERL_NIF_TERM input_record_term;
  unsigned cnt_input_record = 10;
  input_record_term = enif_make_tuple(env, cnt_input_record, input_record_name_term, meterADDR_term, collector2_term, collector1_term, info_term, info_datalen_term, route1_term, route2_term, isBCD_term, subSEQ_term);

  ERL_NIF_TERM output_record_name_term, func_result_term, data_term, frame_term, error_term, data_len_term, frame_len_term, err_len_term;
  output_record_name_term = make_atom(env, OUTPUT_RECORD_NAME);
  func_result_term = enif_make_int(env, func_result);
  data_term = enif_make_string_len(env, out.data, out.data_len, ERL_NIF_LATIN1);
  frame_term = enif_make_string_len(env, out.frame, out.frame_len, ERL_NIF_LATIN1);
  error_term = enif_make_string_len(env, out.error, out.err_len, ERL_NIF_LATIN1);
  data_len_term = enif_make_int(env, out.data_len);
  frame_len_term = enif_make_int(env, out.frame_len);
  err_len_term = enif_make_int(env, out.err_len);
  ERL_NIF_TERM output_record_term;
  unsigned cnt_output_record = 8;
  output_record_term = enif_make_tuple(env, cnt_output_record, output_record_name_term, data_term, frame_term, error_term, data_len_term, frame_len_term, err_len_term, func_result_term);


  ERL_NIF_TERM return_term;
  return_term = enif_make_tuple2(env, input_record_term, output_record_term);

  return make_ok_tuple(env, return_term);
}

static ErlNifFunc nif_funs[] =
  {
    {"exec_func", 3, exec_func_nif}
  };

#define ERL_NIF_INIT_PACKET(NAME, FUNCS, LOAD, RELOAD, UPGRADE, UNLOAD) ERL_NIF_INIT(NAME, FUNCS, LOAD, RELOAD, UPGRADE, UNLOAD)

ERL_NIF_INIT_PACKET(NIF_MODULE, nif_funs, NULL, NULL, NULL, NULL)
