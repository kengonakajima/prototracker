#pragma once

#include "Value.h"
#include "CopyBuffer.h"

struct FileSection;

struct TrackEditorState
{
	Value currentRow;
	Value currentTrack;
	Value currentColumn;
	Value editSkip;
	
	int blockStart, blockEnd;
	
	TrackEditorState();
	
	FileSection * pack();
	bool unpack(const FileSection& section);
};

struct EditorState
{
	Value macro;
	Value octave;
	Value editMode;
	
	TrackEditorState sequenceEditor;
	TrackEditorState patternEditor;
	TrackEditorState macroEditor;
	
	CopyBuffer copyBuffer;
	
	bool followPlayPosition;
	
	EditorState();
	
	FileSection * pack();
	bool unpack(const FileSection& section);
};
