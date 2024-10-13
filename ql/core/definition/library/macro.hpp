#pragma once

#if defined(QL_USE_VULKAN) || defined(QL_USE_ALL)
#define QL_VULKAN
#endif
#if defined(QL_USE_GLM) || defined(QL_USE_ALL)
#define QL_GLM
#endif
#if !defined(QL_NO_SFML) || defined(QL_USE_ALL)
#define QL_SFML
#define QL_GRAPHIC
#endif
#if (defined(QL_USE_GLEW) && !defined(QL_NO_SFML)) || defined(QL_USE_ALL)
#define QL_GLEW
#endif

#if (defined(QL_SOURCE) && !defined(QL_GLEW))
#define QL_STATIC_GLEW
#endif

#if defined _WIN32
#define QL_WINDOWS
#endif