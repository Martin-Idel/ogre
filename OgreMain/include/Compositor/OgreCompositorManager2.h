/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2013 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef __CompositorManager2_H__
#define __CompositorManager2_H__

#include "OgreHeaderPrefix.h"
#include "OgreCompositorCommon.h"
#include "OgreIdString.h"

#include "OgreTexture.h"

namespace Ogre
{
	typedef vector<TexturePtr>::type TextureVec;

	//class _OgreExport CompositorManager2 : public ResourceManager
	class _OgreExport CompositorManager2 : public ResourceAlloc
	{
		typedef map<IdString, CompositorNodeDef*>::type CompositorNodeDefMap;
		CompositorNodeDefMap	mNodeDefinitions;

		typedef map<IdString, CompositorWorkspaceDef*>::type CompositorWorkspaceDefMap;
		CompositorWorkspaceDefMap mWorkspaceDefs;

		typedef vector<CompositorWorkspace*>::type WorkspaceVec;
		WorkspaceVec			mWorkspaces;

		RenderSystem			*mRenderSystem;

		void validateNodes(void);

	public:
		CompositorManager2();
		~CompositorManager2();

		/** The final rendering is done by passing the RenderWindow to one of the input
			channels. This functions does exactly that.
		*/
		void connectOutput( CompositorNode *finalNode, size_t inputChannel );

		/// Finds the requested ShadowNode. Throws if not found.
		CompositorShadowNode* findShadowNode( IdString nodeName ) const;

		/** Finds the requested Camera. Throws if not found.
		@remarks
			If cameraName is empty, uses the default camera
		*/
		Camera* findCamera( IdString cameraName ) const;

		bool hasNodeDefinition( IdString nodeDefName ) const;

		const CompositorNodeDef* getNodeDefinition( IdString nodeDefName ) const;

		CompositorNodeDef* addNodeDefinition( IdString name );

		CompositorWorkspaceDef* addWorkspaceDefinition( IdString name );

		/**
		@param defaultVp
			Default viewport to use when a camera name wasn't specified explicitly in a
			pass definition. This pointer can be null if you promise to use all explicit
			camera names in your passes (and those cameras already exist)
		*/
		void addWorkspace( SceneManager *sceneManager, RenderTarget *finalRenderTarget,
							Camera *defaultCam, IdString definitionName, bool bEnabled );

		void _update( bool swapFinalTargets, bool waitForVSync );
		void _swapAllFinalTargets( bool waitForVSync );
	};
}

#include "OgreHeaderSuffix.h"

#endif