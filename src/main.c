#include "conTMaker.h"

int main(int argc, char ** argv)
{
    conTMaker_t testT = contmakerInit();
    testT->setTitle("TITULO DE PRUEBA!");
    testT->setSubtitle("Este es el subtitulo de la prueba.");
    testT->setDescription("Esta es la descripcion de la herramienta que se mostrara. Abajo estan enumeradas las opciones\ny todas sus descripciones.");
    testT->setPrompt("contmaker@prompt(h for help) > ");

    testT->loop();
    return 0;
}