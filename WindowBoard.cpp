/*
 * Copyright (c) 2015 Markus Himmel
 * This file is distributed under the terms of the MIT license
 */

#include "WindowBoard.h"
#include "Game.h"

#include <Box.h>
#include <StringView.h>
#include <Button.h>
#include <LayoutBuilder.h>
#include <Alert.h>

GameWindow::GameWindow(WindowBoard *master)
	:
	BWindow(BRect(100, 100, 500, 400), "Haiku2048", B_TITLED_WINDOW, 0),
	fMaster(master)
{
	BButton *newGameButton = new BButton("newgame", "New Game",
		new BMessage(H2048_NEW_GAME));

	fScore = new BStringView("score", "Score: 0");

	fBoard = new BBox("gamebox");

	BLayoutBuilder::Group<>(this, B_VERTICAL)
		.SetInsets(B_USE_WINDOW_SPACING)
		.AddGroup(B_HORIZONTAL)
			.Add(newGameButton)
			.Add(fScore)
			.End()
		.Add(fBoard);
}

GameWindow::~GameWindow()
{
}

void
GameWindow::MessageReceived(BMessage *message)
{
	switch (message->what)
	{
		case H2048_NEW_GAME:
		{
			BMessenger game(NULL, fMaster->fTarget);
			game.SendMessage(message);
			break;
		}
		default:
			BWindow::MessageReceived(message);
			break;
	}
}

void
GameWindow::showBoard()
{
}

WindowBoard::WindowBoard(Game *target)
	:
	GameBoard(target),
	fWindow(this)
{
	fWindow.Show();
}

WindowBoard::~WindowBoard()
{
}

void
WindowBoard::gameStarted()
{

	(new BAlert("Title", "Game Started", "OK"))->Go();
}

void
WindowBoard::gameEnded()
{
	(new BAlert("Title", "Game Ended", "OK"))->Go();
}

void
WindowBoard::moveMade()
{
	(new BAlert("Title", "Move Made", "OK"))->Go();
}