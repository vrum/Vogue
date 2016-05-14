// ******************************************************************************
// Filename:    RoomManager.h
// Project:     Vox
// Author:      Steven Ball
//
// Purpose:
//
// Revision History:
//   Initial Revision - 13/04/16
//
// Copyright (c) 2005-2016, Steven Ball
// ******************************************************************************

#pragma once

#include "../Maths/3dmaths.h"

#include <stdio.h>

class RoomManager
{
public:
	/* Public methods */
	RoomManager();
	~RoomManager();

	void Update(float dt);

    void Render();

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
};
