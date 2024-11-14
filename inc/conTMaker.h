#ifndef CONTMAKER_HEADER
#define CONTMAKER_HEADER

/* ---- LIBRARIES ---- */
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* ---- DEFINES ---- */
#define CONTMAKER_TITLE_MAX_BUFFER 32           
#define CONTMAKER_SUBTITLE_MAX_BUFFER 96
#define CONTMAKER_PROMPT_MAX_BUFFER 32
#define CONTMAKER_INPUT_MAX_BUFFER 24
#define CONTMAKER_OPTS_MAX_BUFFER 24
#define CONTMAKER_OPTS_NAME_MAX_BUFFER 8
#define CONTMAKER_DESC_MAX_BUFFER 128


/* ---- CONTMAKER DATA TYPES AND DATA STRUCTURES ---- */
enum conTMaker_e
{
    CONTMAKER_ADDOPT_REPEATED_ERR = -9,
    CONTMAKER_ADDOPT_DESC_LENGTH_ERR = -8,
    CONTMAKER_ADDOPT_NAME_LENGTH_ERR = -7,
    CONTMAKER_ADDOPT_SPACE_ERR = -7,
    CONTMAKER_ADDOPT_NULL_ERR = -6,

    CONTMAKER_SETTER_LENGTH_ERR = -5,
    CONTMAKER_SETTER_NULL_ERR = -4,

    CONTMAKER_INIT_OPTSLEN_ERR = -3,
    CONTMAKER_INIT_ALLOC_ERR = -2,

    CONTMAKER_ERR = -1,
    CONTMAKER_OK
};
typedef enum conTMaker_e CONTMAKER_STATUS;


struct conTMaker_s
{
    // Members //
    uint8_t _titleText[CONTMAKER_TITLE_MAX_BUFFER];
    size_t _titleTextLen;
    uint8_t _subtitleText[CONTMAKER_SUBTITLE_MAX_BUFFER];
    size_t _subtitleTextLen;
    uint8_t _descriptionText[CONTMAKER_DESC_MAX_BUFFER];
    size_t _descriptionTextLen;

    uint8_t _prompt[CONTMAKER_PROMPT_MAX_BUFFER];
    size_t _promptLen;

    uint8_t _input[CONTMAKER_INPUT_MAX_BUFFER];

    uint8_t _opts[CONTMAKER_OPTS_MAX_BUFFER][CONTMAKER_OPTS_NAME_MAX_BUFFER];
    uint8_t _optsLen;
    uint8_t _optsDescription[CONTMAKER_OPTS_MAX_BUFFER][CONTMAKER_DESC_MAX_BUFFER];
    void (*_optsCallback[CONTMAKER_OPTS_MAX_BUFFER])(void);

    // Functionality //
    void (*loop)(void);
    CONTMAKER_STATUS (*addOption)(const unsigned char * optName, const unsigned char * optDescription, const void (*optCallback)(void));


    CONTMAKER_STATUS (*setTitle)(const unsigned char * title);
    CONTMAKER_STATUS (*setSubtitle)(const unsigned char * subtitle);
    CONTMAKER_STATUS (*setDescription)(const unsigned char * description);
    CONTMAKER_STATUS (*setPrompt)(const unsigned char * prompt);

    const char * (*getTitle)(void);
    const char * (*getSubtitle)(void);
    const char * (*getDescription)(void);
    const char * (*getPrompt)(void);
};
typedef struct conTMaker_s conTMaker_h;
typedef conTMaker_h * conTMaker_t;


/* ---- FUNCTIONS PROTOTYPES ---- */
conTMaker_t contmakerInit(void);

#endif