loki_create_lib(
  NAME text
  HEADERS AnimatedText.hpp AnimatedTextStyle.hpp AnnotatedText.hpp Stylesheet.hpp TextAnimationViewData.hpp
  INTERNAL_HEADERS impl/AnimatedGlyph.hpp
  SOURCES AnimatedText.cpp AnimatedTextStyle.cpp AnnotatedText.cpp Stylesheet.cpp TextAnimationViewData.cpp
          impl/AnimatedGlyph.cpp
  PUBLIC_DEPS sfml-graphics loki::common loki::anim loki::styles)
