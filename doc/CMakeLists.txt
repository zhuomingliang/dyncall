find_package(LATEX)
if(PDFLATEX_COMPILER)
  ADD_CUSTOM_COMMAND(
    OUTPUT  manual.pdf
    COMMAND ${PDFLATEX_COMPILER}
    ARGS manual.tex
    DEPENDS manual.tex
  )
endif()

ADD_CUSTOM_TARGET(manual-pdf ALL echo DEPENDS manual.pdf)

# INCLUDE("${PROJECT_SOURCE_DIR}/buildsys/cmake/Modules/UseLATEX.cmake")
# set(LATEX_OUTPUT_PATH tmp)
# add_latex_document(manual.tex DEFAULT_PDF)

