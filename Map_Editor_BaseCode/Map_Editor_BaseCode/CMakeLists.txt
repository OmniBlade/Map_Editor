PROJECT(MAPEDITOR)
SET( PACKAGE "mapeditor" )
cmake_minimum_required(VERSION 2.6)

SET(VERSION "0.0.1")

IF(NOT MSVC)
  SET( WARN_FLAGS "-Wall -Wno-long-long -Wno-variadic-macros" )
  SET( WARN_FLAGS_DEBUG "-Wextra -Weffc++ -pedantic -Wold-style-cast -Woverloaded-virtual -Wctor-dtor-privacy -Wreorder -Wabi -Wstrict-null-sentinel -Wc++0x-compat -Wformat=2 -Winit-self -Wswitch-default -Wsign-conversion -Wlogical-op -Wmissing-declarations -Wmissing-noreturn -Wmissing-format-attribute -Wredundant-decls -Winline" )
  # Don't enable these for now, but leave them around to investigate closer later
  SET( WARN_FLAGS_DEBUG_EXCESSIVE "-Wpadded -Wunreachable-code -Wconversion" )
  SET( CMAKE_CXX_FLAGS "${WARN_FLAGS} -fPIC ${CMAKE_CXX_FLAGS}" )
  SET( CMAKE_CXX_FLAGS_DEBUG "${WARN_FLAGS_DEBUG} -g -O0 ${CMAKE_CXX_FLAGS_DEBUG}" )
ENDIF(NOT MSVC)

SET( MAPEDITOR_VERSION_INFO "${VERSION}" )

include_directories(${MAPEDITOR_SOURCE_DIR})

SET( MAPEDITOR_SRCS 
  Editor.Map.Validator/Basic/BasicValidator.cpp
  Editor.Engine/Basics/Basic.cpp
  Editor.Map.Validator/AI/AIValidator.cpp
  Editor.Engine/Types/AI/AITriggerEnable.cpp
  Editor.Engine/Types/AI/AITriggerType.cpp
  Editor.FileSystem/CsfFile/CSFEntry.cpp
  Editor.FileSystem/FileManager/Managers/CSFManager.cpp
  Editor.FileSystem/CsfFile/CSFFile.cpp
  Editor.Engine/Types/Triggers/CellTag.cpp
  Editor.Engine/Types/Triggers/Action.cpp
  Editor.Engine/Types/BaseNode.cpp
  Editor.Configuration/ConfigFile.cpp
  Editor.Configuration/ConfigLoader.cpp
  Editor.Engine/Types/Objects/Aircraft.cpp
  Editor.Objects.Westwood/Types/Country.cpp
  Editor.Objects.Westwood/General/CombatDamage.cpp
  Editor.Objects.Westwood/General/AudioVisual.cpp
  Editor.Objects.Westwood/General/AI.cpp
  Editor.Engine/Map/Map.cpp
  Editor.Objects.Westwood/Types/Animation.cpp
  Editor.Objects.Westwood/Types/AircraftType.cpp
  Editor.Objects.Westwood/Types/InfantryType.cpp
  Editor.Objects.Westwood/Types/Foundation.cpp
  Editor.Objects.Westwood/Types/AbstractType.cpp
  Editor.FileSystem/PaletteFile/PaletteFile.cpp
  Editor.Engine/Loading/MapObjectLoader.cpp
  Editor.Engine/Loading/WWLoader.cpp
  Editor.Objects.Westwood/Types/ObjectType.cpp
  Editor.Objects.Westwood/Types/BuildingType.cpp
  Editor.FileSystem/MixFile/Blowfish.cpp
  Editor.FileSystem/MixFile/Ccrc.cpp
  Editor.FileSystem/MixFile/KeyCalculator.cpp
  Editor.FileSystem/MixFile/MixFile.cpp
  Editor.FileSystem/FileManager/FileSystem.cpp
  Editor.FileSystem/ShpFile/Format3.cpp
  Config.cpp
  Editor.FileSystem/FileManager/Managers/MixManager.cpp
  Editor.FileSystem/FileManager/Managers/INIManager.cpp
  Editor.Engine/Loading/StartupLoader.cpp
  Editor.FileSystem/HvaFile/HVAFile.cpp
  Editor.Objects.Westwood/General/General.cpp
  Editor.Engine/Types/Objects/Infantry.cpp
  Editor.Engine/Types/House.cpp
  Editor.Objects.Westwood/General/IQ.cpp
  Editor.Engine/Types/Triggers/Event.cpp
  Editor.Engine/Game/GameMode.cpp
  Editor.Engine/Game/GameModeCollection.cpp
  Editor.Engine/Basics/Lighting.cpp
  Editor.FileSystem/MapFile/Triggers/EventCollection.cpp
  Editor.FileSystem/MapFile/Triggers/EventType.cpp
  Editor.Engine/Map/Packs/IsoMapPack.cpp
  Editor.FileSystem/EncFile/EncFile.cpp
  Editor.FileSystem/FileManager/Managers/EncManager.cpp
  Editor.FileSystem/MapFile/Compression/Format80.cpp
  Editor.Map.Validator/Trigger/EventValidator.cpp
  Editor.Objects.Westwood/General/GameColor.cpp
  Editor.FileSystem/FileManager/FileWriter.cpp
  GameDefinition.cpp
  Editor.FileSystem/MapFile/MapWriter.cpp
  Editor.Engine/Loading/GenericLoader.cpp
  Log.cpp
  Editor.Engine/Basics/MapStats.cpp
  Editor.FileSystem/MapFile/Modifications/MapMods.cpp
  Editor.Engine/Loading/MapLoader.cpp
  Map_Editor_BaseCode.cpp
  Editor.Objects.Westwood/Types/OverlayType.cpp
  Editor.FileSystem/FileManager/BinaryReader.cpp
  Editor.FileSystem/IniFile/LineSplitter.cpp
  Editor.FileSystem/IniFile/INIFile.cpp
  Editor.FileSystem/IniFile/INISection.cpp
  Editor.Objects.Westwood/Types/SmudgeType.cpp
  Editor.FileSystem/FileManager/RawFileSystem.cpp
  Editor.FileSystem/FileManager/Managers/PALManager.cpp
  Editor.FileSystem/ShpFile/ShpFile.cpp
  Editor.FileSystem/ShpFile/ShpImage.cpp
  Editor.FileSystem/FileManager/Managers/SHPManager.cpp
  Editor.Objects.Westwood/Types/ParticleType.cpp
  Editor.Objects.Westwood/Types/ProjectileType.cpp
  Editor.Objects.Westwood/General/SpecialWeapon.cpp
  Editor.Map.Validator/Object/ObjectValidator.cpp
  Editor.Objects.Westwood/General/Side.cpp
  Editor.Engine/Types/TeamTypes/ScriptType.cpp
  Editor.Engine/Types/TeamTypes/ScriptAction.cpp
  Editor.Objects.Westwood/AudioVisual/Sound.cpp
  Editor.Objects.Westwood/AudioVisual/Speech.cpp
  Editor.Engine/Types/Smudge.cpp
  Editor.Map.Validator/Basic/MiscValidator.cpp
  Editor.Map.Validator/Object/OverlayValidator.cpp
  Editor.Engine/Basics/SpecialFlag.cpp
  Editor.FileSystem/MapFile/Triggers/SActionCollection.cpp
  Editor.FileSystem/MapFile/Triggers/SActionType.cpp
  Editor.FileSystem/MapFile/Triggers/ParamCollection.cpp
  Editor.FileSystem/MapFile/Triggers/ParamType.cpp
  Editor.Engine/Map/Packs/PackType.cpp
  Editor.Engine/Map/Packs/OverlayPack.cpp
  Editor.Engine/Types/Overlay.cpp
  Editor.Objects.Westwood/AudioVisual/Movie.cpp
  Editor.Objects.Westwood/OverlayTypeValidator.cpp
  Editor.Engine/Map/Packs/PreviewPack.cpp
  Editor.FileSystem/MapFile/Flushing/NameFlusherClass.cpp
  Editor.Engine/Basics/Ranking.cpp
  Editor.Engine/Types/Objects/Object.cpp
  Editor.FileSystem/VoxelFile/Section.cpp
  stdafx.cpp
)

ADD_EXECUTABLE(mapeditor ${MAPEDITOR_SRCS})
