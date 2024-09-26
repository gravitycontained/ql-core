#pragma once

#ifndef QL
#ifdef QL_EXPORT
#define QL __declspec(dllexport)
#else
#define QL __declspec(dllimport)
#endif
#endif