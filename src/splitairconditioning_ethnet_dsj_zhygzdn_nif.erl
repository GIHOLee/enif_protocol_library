-module(splitairconditioning_ethnet_dsj_zhygzdn_nif).

-export([exec_func/3]).

-on_load(init/0).

init() ->
    NifName = ?MODULE_STRING,
    PrivDir = 
        case code:priv_dir("enif_protocol_library") of
            {error, bad_name} ->
                "priv";
            Dir ->
                Dir
        end,
    NifFileName = filename:join(PrivDir, NifName),
    erlang:load_nif(NifFileName, 0).
            
exec_func(_FuncName, _Input, _Output) ->
    error:nif_error(nif_library_not_loaded).
