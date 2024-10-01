#pragma once

#if defined(QL_USE_VULKAN) || defined(QL_USE_ALL)
#define QL_INTERN_VULKAN_USE
#endif
#if defined(QL_USE_GLM) || defined(QL_USE_ALL)
#define QL_INTERN_GLM_USE
#endif
#if !defined(QL_NO_SFML) || defined(QL_USE_ALL)
#define QL_INTERN_SFML_USE
#endif
#if (defined(QL_USE_GLEW) && !defined(QL_NO_SFML)) || defined(QL_USE_ALL)
#define QL_INTERN_GLEW_USE
#endif

#if (defined(QLDLL_EXPORTS) && !defined(QL_INTERN_GLEW_USE))
#define QL_INTERN_STATIC_NO_GLEW
#endif

#ifdef _WIN32
#define QL_WINDOWS
#endif