INCLUDE("${PROJECT_SOURCE_DIR}/buildsys/cmake/Modules/UseLATEX.cmake")

add_latex_document(manual.tex DEFAULT_PDF)
set(LATEX_OUTPUT_PATH tmp)

