#pragma once

#ifndef QL_SOURCE
#if defined QL_EXPORT
#define QL_SOURCE __declspec(dllexport)
#else
#define QL_SOURCE __declspec(dllimport)
#endif
#endif