add_library(lib_core
	Dice.h
	Dice.cpp
	Card.h 
	ResourceCard.h
	ResourceCard.cpp "CardFactory.h" "CardFactory.cpp" "GameManager.h" "GameManager.cpp" "Level.h" "Level.cpp" "LevelFactory.h" "LevelFactory.cpp"
		Renderer.cpp
		Renderer.h
		AudioManager.cpp
		AudioManager.h)
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC pugixml sfml-graphics sfml-audio)
