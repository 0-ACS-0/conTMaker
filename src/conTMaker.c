#include "conTMaker.h"

/* ---- GLOBAL VARIABLE ---- */
conTMaker_t __contmaker;

/* ---- STATIC FUNCTIONS PROTOTYPES ---- */
static void contmakerLoop();
static CONTMAKER_STATUS contmakerAddOption(const unsigned char * optName, const unsigned char * optDescription, const void (*optCallback)(void));

static void contmakerShowPrompt(void);
static void contmakerWaitInput(void);

static void contmakerCmd(void);
static void contmakerShowHelp(void);
static void contmakerQuit(void);

static CONTMAKER_STATUS contmakerSetTitle(const unsigned char * title);
static CONTMAKER_STATUS contmakerSetSubtitle(const unsigned char * subtitle);
static CONTMAKER_STATUS contmakerSetDescription(const unsigned char * description);
static CONTMAKER_STATUS contmakerSetPrompt(const unsigned char * promptText);

static const char * contmakerGetTitle(void);
static const char * contmakerGetSubtitle(void);
static const char * contmakerGetDescription(void);
static const char * contmakerGetPrompt(void);


/* --------------------------------------------- */
/* ---- MANDATORY FUNCTIONS IMPLEMENTATIONS ---- */
/* --------------------------------------------- */

/*

*/
conTMaker_t contmakerInit(void)
{
    // Memory allocation and initialization to zeros:
    if ((__contmaker = (conTMaker_t)malloc(sizeof(conTMaker_h))) == NULL){return NULL;}
    *__contmaker = (conTMaker_h){0};

    // Functionality reference bind to data structure.
    __contmaker->loop = contmakerLoop;
    __contmaker->addOption = contmakerAddOption;

    __contmaker->setTitle = contmakerSetTitle;
    __contmaker->setSubtitle = contmakerSetSubtitle;
    __contmaker->setDescription = contmakerSetDescription;
    __contmaker->setPrompt = contmakerSetPrompt;

    __contmaker->getTitle = contmakerGetTitle;
    __contmaker->getSubtitle = contmakerGetSubtitle;
    __contmaker->getDescription = contmakerGetDescription;
    __contmaker->getPrompt = contmakerGetPrompt;

    return __contmaker;
}








/* --------------------------------------- */
/* ---- SETTERS AND GETTERS FUNCTIONS ---- */
/* --------------------------------------- */
/*

*/
static CONTMAKER_STATUS contmakerSetTitle(const unsigned char * title)
{
    // Local variables:
    const size_t titleLen = strlen(title);
    
    // Checks:
    if (__contmaker == NULL){return CONTMAKER_SETTER_NULL_ERR;}
    if ((titleLen) > CONTMAKER_TITLE_MAX_BUFFER){return CONTMAKER_SETTER_LENGTH_ERR;}

    // Data write:
    strcpy(__contmaker->_titleText, title);
    __contmaker->_titleTextLen = titleLen;
}

/*

*/
static CONTMAKER_STATUS contmakerSetSubtitle(const unsigned char * subtitle)
{
    // Local variables:
    const size_t subtitleLen = strlen(subtitle);

    // Checks:
    if (__contmaker == NULL){return CONTMAKER_SETTER_NULL_ERR;}
    if (subtitleLen > CONTMAKER_SUBTITLE_MAX_BUFFER){return CONTMAKER_SETTER_LENGTH_ERR;}

    // Data write:
    strcpy(__contmaker->_subtitleText, subtitle);
    __contmaker->_subtitleTextLen = subtitleLen;
}

/*

*/
static CONTMAKER_STATUS contmakerSetDescription(const unsigned char * description)
{
    // Local variables:
    const size_t descriptionLen = strlen(description);

    // Checks:
    if (__contmaker == NULL){return CONTMAKER_SETTER_NULL_ERR;}
    if (descriptionLen > CONTMAKER_DESC_MAX_BUFFER){return CONTMAKER_SETTER_LENGTH_ERR;}

    // Data write:
    strcpy(__contmaker->_descriptionText, description);
    __contmaker->_descriptionTextLen = descriptionLen;
}

/*

*/
static CONTMAKER_STATUS contmakerSetPrompt(const unsigned char * promptText)
{
    // Local variables:
    const size_t promptTextLen = strlen(promptText);

    // Checks:
    if (__contmaker == NULL){return CONTMAKER_SETTER_NULL_ERR;}
    if (promptTextLen > CONTMAKER_PROMPT_MAX_BUFFER){return CONTMAKER_SETTER_LENGTH_ERR;}

    // Data write:
    strcpy(__contmaker->_prompt, promptText);
    __contmaker->_promptLen = promptTextLen;
}

//// //// //// //// //// //// //// ////

/*

*/
static const char * contmakerGetTitle(void)
{
    // Checks:
    if (__contmaker == NULL){return NULL;}

    // Read-only text reference return value:
    return (const char *)__contmaker->_titleText;
}

/*

*/
static const char * contmakerGetSubtitle(void)
{
    // Checks:
    if (__contmaker == NULL){return NULL;}


    // Read-only text reference return value:
    return (const char *)__contmaker->_subtitleText;
}

/*

*/
static const char * contmakerGetDescription(void)
{
    // Check:
    if (__contmaker == NULL){return NULL;}
    
    // Read-only text reference return value:
    return (const char *)__contmaker->_descriptionText;
}

/*

*/
static const char * contmakerGetPrompt(void)
{
    // Checks:
    if (__contmaker == NULL){return NULL;}

    // Read-only text reference return value:
    return (const char *)__contmaker->_prompt;
}







/* ----------------------------------- */
/* ---- FUNCTIONS IMPLEMENTATIONS ---- */
/* ----------------------------------- */

/*

*/
static void contmakerLoop(void)
{
    // Reserved commands:
    __contmaker->addOption("h", "Muestra la ayuda de la herramienta.", contmakerShowHelp);
    __contmaker->addOption("q", "Sale de la aplicacion.", contmakerQuit);

    while(1)
    {
        printf("\n");
        contmakerShowPrompt();
        contmakerWaitInput();

        contmakerCmd();
    }

}

/*

*/
static CONTMAKER_STATUS contmakerAddOption(const unsigned char * optName, const unsigned char * optDescription, const void (*optCallback)(void))
{
    // Local variables:
    const size_t optNameLenght = strlen(optName);
    const size_t optDescriptionLength = strlen(optDescription);

    // Checks: 
    if (__contmaker == NULL){return CONTMAKER_ADDOPT_NULL_ERR;}
    if (__contmaker->_optsLen >= CONTMAKER_OPTS_MAX_BUFFER){return CONTMAKER_ADDOPT_SPACE_ERR;}

    if (optNameLenght > CONTMAKER_OPTS_NAME_MAX_BUFFER){return CONTMAKER_ADDOPT_NAME_LENGTH_ERR;}
    if (optDescriptionLength > CONTMAKER_DESC_MAX_BUFFER){return CONTMAKER_ADDOPT_DESC_LENGTH_ERR;}

    for (int i = 0; i < __contmaker->_optsLen; i++){if(!strcmp(optName, __contmaker->_opts[i])){return CONTMAKER_ADDOPT_REPEATED_ERR;}}

    // Addition of the new option data to contmaker data structure:
    strcpy(__contmaker->_opts[__contmaker->_optsLen], optName);
    strcpy(__contmaker->_optsDescription[__contmaker->_optsLen], optDescription);
    __contmaker->_optsCallback[__contmaker->_optsLen] = optCallback;

    // Increment of opts len:
    __contmaker->_optsLen++;

    return CONTMAKER_OK;
}







/* -------------------------------------------- */
/* ---- AUXILIAR FUNCTIONS IMPLEMENTATIONS ---- */
/* -------------------------------------------- */

/*

*/
static void contmakerShowPrompt(void)
{
    // Checks:
    if ((__contmaker == NULL) || (__contmaker->_promptLen == 0)){return;}

    // Prints the prompt text into the standard output:
    printf(__contmaker->_prompt);
}

/*

*/
static void contmakerWaitInput(void)
{
    // Local variables:
    uint8_t auxInput[CONTMAKER_INPUT_MAX_BUFFER * 2] = {'\0'}; 

    // Checks:
    if (__contmaker == NULL){return;}

    // Clear the input buffer:
    memset(__contmaker->_input, '\0', CONTMAKER_INPUT_MAX_BUFFER);

    // User input read:
    fgets((char *)auxInput, CONTMAKER_INPUT_MAX_BUFFER * 2, stdin);

    // Overflow handling:
    if (auxInput[CONTMAKER_INPUT_MAX_BUFFER - 1] != '\0')
    {
        // Overflow exists //

        // Truncation of auxilizar input and copy to input member:
        auxInput[CONTMAKER_INPUT_MAX_BUFFER - 1] = '\0';
        strcpy((char *)__contmaker->_input, (char *)auxInput);

        // Discard of remaining input:
        do
        {
            memset(auxInput, '\0', CONTMAKER_INPUT_MAX_BUFFER * 2);
            fgets((char *)auxInput, CONTMAKER_INPUT_MAX_BUFFER * 2, stdin);
        } while (auxInput[CONTMAKER_INPUT_MAX_BUFFER - 1] != '\0');
        

        return;
    }
    else
    {
        // No overflow //

        // Copy auxiliar input to input member:
        strcpy((char *)__contmaker->_input, (char *)auxInput);

        // Remove newline character:
        size_t inLen = strlen(__contmaker->_input);
        if ((inLen > 0) && (__contmaker->_input[inLen - 1] == '\n'))
        {
            __contmaker->_input[inLen - 1] = '\0';
        }

        return;
    }
}

/*

*/
static void contmakerCmd(void)
{
    // Checks:
    if (__contmaker == NULL){return;}

    // Exectues the corresponding callback for the option received:
    for (int i = 0; i < __contmaker->_optsLen; i++)
    {
        if (!strcmp(__contmaker->_input, __contmaker->_opts[i]))
        {
            __contmaker->_optsCallback[i]();
            return;
        }
    }
}

/*

*/
static void contmakerShowHelp(void)
{
    // Cabecera //
    printf("\n%s", __contmaker->_titleText);
    printf("\n%s\n", __contmaker->_subtitleText);
    for(int i = 0; i < __contmaker->_subtitleTextLen * 2; i++){printf("-");}
    printf("\n%s\n", __contmaker->_descriptionText);

    // Opciones y descripciones //
    printf("\n\n[OPCIONES]: \n");
    for(int i = 0; i < __contmaker->_optsLen; i++)
    {
        printf(" > %s: ", __contmaker->_opts[i]);
        printf("%s \n", __contmaker->_optsDescription[i]);
    }
}

/*

*/
static void contmakerQuit(void)
{
    exit(0);
}