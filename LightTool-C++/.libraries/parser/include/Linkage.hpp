#pragma once

#ifdef PARSER_MIGUEL

#define PARSER_MIGUEL_API __declspec(dllexport)

#else

#define PARSER_MIGUEL_API __declspec(dllimport)

#endif