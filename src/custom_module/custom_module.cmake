set(TEMPLATE_START "//This file is generated automatically by the program and is not allowed to be modified manually!\n\
//This file is generated automatically by the program and is not allowed to be modified manually!\n\
//This file is generated automatically by the program and is not allowed to be modified manually!\n\n\
#include \"custom_module/custom_module.h\"\n")

set(TEMPLATE_SOURCE_START "\nCustomModule::CustomModule(std::map<std::string, Module *> *modules, System *system)\n\
{\n")

set(TEMPLATE_END "}\n\n\
CustomModule::~CustomModule()\n\
{\n\
}\n")

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
    set(HEADER "")
    set(SOURCE "")
    foreach(module ${MODULESUBDIRS})
        string(TOLOWER ${module} MODULE_LOWER)
        set(MODULE_LOWER "${MODULE_LOWER}__")
        string(TOUPPER ${module} MODULE_UPPER)

        set(HEADER "${HEADER}#if ${MODULE_UPPER}\n#include \"custom_module/${module}.h\"\n#endif\n")
     
        set(code "\n#if ${MODULE_UPPER}\n")
        set(code "${code}\t${module} *${MODULE_LOWER} = new ${module}(system);\n")
        set(code "${code}\tmodules.insert(std::pair<std::string, Module *>(typeid(*${MODULE_LOWER}).name(),${MODULE_LOWER}));\n")
        set(code "${code}#endif\n\n")
        set(SOURCE ${SOURCE}${code})
        # message(${module})
    endforeach()
    set(SOURCE ${TEMPLATE_START}${HEADER}${TEMPLATE_SOURCE_START}${SOURCE}${TEMPLATE_END})
    file(WRITE ${dir}/custom_module.cpp "${SOURCE}")

endfunction()