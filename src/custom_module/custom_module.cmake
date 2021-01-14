set(TEMPLATE_START "//This file is generated automatically by the program and is not allowed to be modified manually!\n\
//This file is generated automatically by the program and is not allowed to be modified manually!\n\
//This file is generated automatically by the program and is not allowed to be modified manually!\n\
#include \"custom_module/custom_module.h\"\n\
CustomModule::CustomModule(std::map<std::string, Module *> *modules, System *system)\n\
{\n")

set(TEMPLATE_END "}\n\n\
CustomModule::~CustomModule()\n\
{\n\
}\n\
{\n")

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()


function(WriteCustomModule dir)
    SUBDIRLIST(MODULESUBDIRS ${dir})
    set(SOURCE ${TEMPLATE_START})
    foreach(module ${MODULESUBDIRS})
        set(obj "${module}_")
        set(code "#if ${module}_ENABLE\n")
        set(code "${code}${module} *${obj} = new ${module}(system_);\n")
        set(code "${code}modules_.insert(std::pair<std::string, Module *>(typeid(*${obj}).name(),${obj}));\n")
        set(code ${code}"#endif\n")

        set(SOURCE ${SOURCE}${code})
        # message(${module})
    endforeach()
    set(SOURCE ${SOURCE}${TEMPLATE_END})
    message("-------------------"${SOURCE})

endfunction()