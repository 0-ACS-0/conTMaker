#include "conTMaker.h"

void printTitle();

int main(int argc, char ** argv)
{
    conTMaker_t testT = contmakerInit();
    testT->setTitle("TITULO DE PRUEBA!");
    testT->setSubtitle("Este es el subtitulo de la prueba.");
    testT->setDescription("Esta es la descripcion de la herramienta que se mostrara. Abajo estan enumeradas las opciones\ny todas sus descripciones.");
    testT->setPrompt("contmaker@prompt(h for help) > ");

    testT->addOption("tits", "Muestra el titulo, sin mas.", printTitle);

    testT->loop();
    return 0;
}

void printTitle()
{
    extern conTMaker_t __contmaker;
    printf("Titulo: %s\n", __contmaker->getTitle());
}