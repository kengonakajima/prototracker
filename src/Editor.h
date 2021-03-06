#pragma once

#include "SDL.h"
#include "Listener.h"

struct PlayerState;
struct Renderer;
struct EditorState;

class Editor: public Listener
{
public:
	static const int maxChildren = 128;
private:
	Editor *mFocus;
	
	void drawModal(Renderer& renderer, const SDL_Rect& area);
	virtual void onDraw(Renderer& renderer, const SDL_Rect& area) = 0;
	void drawChildren(Renderer& renderer, const SDL_Rect& area);
	
protected:
	Editor *mModal;
	EditorState& mEditorState;
	bool mIsDirty, mRedraw;
	Editor *mParent;
	Editor *mChildren[maxChildren];
	SDL_Rect mChildrenArea[maxChildren];
	int mNumChildren;
	bool mWantsFocus;
	
	void removeFocus();
	void setModal(Editor *modal);
	
	void invalidateAll();
	void invalidateParent();
	
	bool shouldRedrawBackground() const;
	
public:
	Editor(EditorState& editorState, bool wantFocus = true);
	virtual ~Editor();
	
	void addChild(Editor *child, int x, int y, int w, int h);
	
	void setDirty(bool dirty);
	virtual void onFileSelectorEvent(const Editor& fileSelector, bool accept);
	virtual void onMessageBoxEvent(const Editor& messageBox, int code);
	virtual void onListenableChange(Listenable *listenable);
	virtual bool isDirty() const;
	bool isFocusable() const;
	bool hasDirty() const;
	void setFocus(Editor *editor);
	Editor * getFocus();
	bool hasFocus();
	
	void draw(Renderer& renderer, const SDL_Rect& area);
	virtual bool onEvent(SDL_Event& event);
};
