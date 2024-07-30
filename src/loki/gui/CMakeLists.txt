loki_create_module(gui
  HEADERS
  Widget.hpp
  # containers
  containers/Grid.hpp
  containers/GridMenuView.hpp
  containers/Group.hpp
  containers/List.hpp
  containers/TextList.hpp
  # elements
  elements/Frame.hpp
  elements/RectangleShapeFrame.hpp
  elements/SpriteFrame.hpp
  elements/SpriteLabel.hpp
  elements/TextBox.hpp
  elements/TextBoxView.hpp
  elements/TextLabel.hpp
  #elements/TiledFrame.hpp
  # widgets/style
  style/FrameStyle.hpp
  style/Stylesheet.hpp
  style/TextBoxStyle.hpp

  SOURCES
  Widget.cpp
  # containers
  containers/Grid.cpp
  containers/GridMenuView.cpp
  containers/Group.cpp
  containers/List.cpp
  containers/TextList.cpp
  # elements
  elements/Frame.cpp
  elements/RectangleShapeFrame.cpp
  elements/SpriteFrame.cpp
  elements/SpriteLabel.cpp
  elements/TextBox.cpp
  elements/TextBoxView.cpp
  elements/TextLabel.cpp
  #elements/TiledFrame.cpp
  # style
  style/Stylesheet.cpp

  PUBLIC_DEPS
  loki::graphics
)