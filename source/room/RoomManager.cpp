// ******************************************************************************
// Filename:    RoomManager.cpp
// Project:     Vox
// Author:      Steven Ball
//
// Revision History:
//   Initial Revision - 13/04/16
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#include "RoomManager.h"
#include "../utils/Random.h"


RoomManager::RoomManager(Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
}

RoomManager::~RoomManager()
{
	ClearRooms();
}

// Clearing
void RoomManager::ClearRooms()
{
	for (unsigned int i = 0; i < m_vpRoomList.size(); i++)
	{
		delete m_vpRoomList[i];
		m_vpRoomList[i] = 0;
	}
	m_vpRoomList.clear();
}

// Generation
void RoomManager::GenerateNewLayout()
{
	ClearRooms();
	CreateRandomRoom(NULL, eDirection_NONE, 0);
}

void RoomManager::CreateRandomRoom(Room* pRoomConnection, eDirection connectedDirection, int roomDepth)
{
	Room* pNewRoom = new Room(m_pRenderer, this);

	float length = GetRandomNumber(30, 80, 2) * 0.1f;
	float width = GetRandomNumber(30, 80, 2) * 0.1f;
	float height = 1.0f;

	pNewRoom->SetDimensions(length, width, height);

	eDirection dontAllowDirection = eDirection_NONE;

	// If we are connected to a room, set our position
	if (pRoomConnection != NULL)
	{
		vec3 newRoomPosition = pRoomConnection->GetPosition();
		if (connectedDirection == eDirection_Up)
		{
			newRoomPosition -= vec3(0.0f, 0.0f, width + pRoomConnection->GetWidth());
			dontAllowDirection = eDirection_Down;
		}
		if (connectedDirection == eDirection_Down)
		{
			newRoomPosition += vec3(0.0f, 0.0f, width + pRoomConnection->GetWidth());
			dontAllowDirection = eDirection_Up;
		}
		if (connectedDirection == eDirection_Left)
		{
			newRoomPosition -= vec3(length + pRoomConnection->GetLength(), 0.0f, 0.0f);
			dontAllowDirection = eDirection_Right;
		}
		if (connectedDirection == eDirection_Right)
		{
			newRoomPosition += vec3(length + pRoomConnection->GetLength(), 0.0f, 0.0f);
			dontAllowDirection = eDirection_Left;
		}

		pNewRoom->SetPosition(newRoomPosition);
	}

	// Create a door and connected room
	if (roomDepth < 2)
	{
		// Don't allow to create doors back to the previously connected room (if we have one)
		// Keep getting a new direction, until we don't match the connected direction.
		eDirection doorDirection = dontAllowDirection;
		while(doorDirection == dontAllowDirection)
		{
			doorDirection = (eDirection)GetRandomNumber(0, 3);
		}

		// Create the door object
		pNewRoom->CreateDoor(doorDirection);

		// Create a new room, that connects to this one
		CreateRandomRoom(pNewRoom, doorDirection, roomDepth+1);
	}

	m_vpRoomList.push_back(pNewRoom);
}

void RoomManager::CreateConnectedRoom()
{
	int randomRoomIndex = GetRandomNumber(0, (int)m_vpRoomList.size());

	Room* pRoom = m_vpRoomList[randomRoomIndex];
}

// Update
void RoomManager::Update(float dt)
{
	for (unsigned int i = 0; i < m_vpRoomList.size(); i++)
	{
		Room *pRoom = m_vpRoomList[i];

		pRoom->Update(dt);
	}
}

// Render
void RoomManager::Render()
{
	m_pRenderer->PushMatrix();
		for (unsigned int i = 0; i < m_vpRoomList.size(); i++)
		{
			Room *pRoom = m_vpRoomList[i];

			pRoom->Render();
		}
	m_pRenderer->PopMatrix();
}