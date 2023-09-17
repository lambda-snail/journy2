java -jar ..\third_party\antlr-4.13.0-complete.jar -Dlanguage=Cpp -listener -visitor -o source/markdown/generated/ -package marky .\Markdown.g4
mkdir -Force ../include/markdown/parser/
rm include/marky/parser/*.h
mv src/generated/*.h include/marky/parser/