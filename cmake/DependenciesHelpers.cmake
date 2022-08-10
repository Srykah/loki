# todo auto add dep to lokiConfig

function(loki_find_dep depName depVer depComps)
  if (${depName}_DIR)
    message("\"${depName}_DIR\" found! Value is \"${${depName}_DIR}\"")
    find_package(${depName} ${depVer} COMPONENTS "${depComps}" CONFIG PATHS "${${depName}_DIR}" NO_DEFAULT_PATH REQUIRED)
    if (NOT ${depName}_FOUND)
      message(SEND_ERROR "${depName} not found; please check ${depName}_DIR (current value: \"${${depName}_DIR}\").")
    endif ()
  else ()
    message("\"${depName}_DIR\" not found! Trying to find it anyway!")
    find_package(${depName} ${depVer} COMPONENTS "${depComps}" CONFIG REQUIRED)
    if (NOT ${depName}_FOUND)
      message(SEND_ERROR "${depName} not found; please set ${depName}_DIR.")
    endif ()
  endif ()
  loki_print_variables_with_pattern(${depName})
endfunction()

function(loki_find_all_deps depList)
  foreach (dep ${depList})
    string(REPLACE "," ";" depData ${dep})
    list(LENGTH depData depDataLen)
    list(GET depData 0 depName)
    string(STRIP ${depName} depName)
    list(GET depData 1 depVer)
    string(STRIP ${depVer} depVer)
    if (depDataLen GREATER 2)
      list(GET depData 2 depComps)
      string(STRIP ${depComps} depComps)
      string(REPLACE " " ";" depComps ${depComps})
    endif ()
    loki_find_dep(${depName} ${depVer} "${depComps}")
  endforeach ()
endfunction()
