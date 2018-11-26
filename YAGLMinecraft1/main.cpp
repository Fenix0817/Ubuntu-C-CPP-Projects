#define _GNU_SOURCE
/*
 * main.cpp
 *
 *  Created on: Sep 14, 2018
 *      Author: jack
 */


#include "Window.h"
#include "Utilities.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include <vector>
#include "Block.h"
#include "TexturePos.h"
#include "Atlas.h"
#include "AtlasPos.h"
#include "AtlasHD.h"
#include "AtlasLow.h"
#include "AtlasNormal.h"
#include "AtlasFogleman.h"
#include "AtlasMCSimple.h"
#include "Chunk.h"
#include "ChunkManager.h"
#include "SelectedBlock.h"
#include "TextAtlas.h"
#include "TextAtlasMonospaced.h"
#include "TextRenderer.h"
#include "Crosshair.h"
#include <signal.h>
#include <cxxabi.h>

#include <utility>

#include "FastNoise.h"

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "Game.h"

//#define DEBUG_FPS
//#define DEBUG_CHUNKMANAGER


#include <execinfo.h>
#include <stdio.h>

//https://oroboro.com/stack-trace-on-crash/
static inline void printStackTrace( FILE *out = stderr, unsigned int max_frames = 63 )
{
   fprintf(out, "stack trace:\n");

   // storage array for stack trace address data
   void* addrlist[max_frames+1];

   // retrieve current stack addresses
   int addrlen = backtrace( addrlist, sizeof( addrlist ) / sizeof( void* ));

   if ( addrlen == 0 )
   {
      fprintf( out, "  \n" );
      return;
   }

   // create readable strings to each frame.
   char** symbollist = backtrace_symbols( addrlist, addrlen );

   // print the stack trace.
   for ( int i = 4; i < addrlen; i++ )
      fprintf( out, "%s\n", symbollist[i]);

   free(symbollist);
}
void abortHandler( int signum ,siginfo_t*p1,void*p2)
{
   // associate each signal with a signal name string.
   const char* name = NULL;
   switch( signum )
   {
   case SIGABRT: name = "SIGABRT";  break;
   case SIGSEGV: name = "SIGSEGV";  break;
   case SIGBUS:  name = "SIGBUS";   break;
   case SIGILL:  name = "SIGILL";   break;
   case SIGFPE:  name = "SIGFPE";   break;
   }

   // Notify the user which signal was caught. We use printf, because this is the
   // most basic output function. Once you get a crash, it is possible that more
   // complex output systems like streams and the like may be corrupted. So we
   // make the most basic call possible to the lowest level, most
   // standard print function.
   if ( name )
      fprintf( stderr, "Caught signal %d (%s)\n", signum, name );
   else
      fprintf( stderr, "Caught signal %d\n", signum );

   // Dump a stack trace.
   // This is the function we will be implementing next.
   printStackTrace();

   // If you caught one of the above signals, it is likely you just
   // want to quit your program right now.
   exit( signum );
}

int main(){
	struct sigaction sa;
   sa.sa_flags = SA_SIGINFO;
   sa.sa_sigaction = abortHandler;
   sigemptyset( &sa.sa_mask );

   sigaction( SIGABRT, &sa, NULL );
   sigaction( SIGSEGV, &sa, NULL );
   sigaction( SIGBUS,  &sa, NULL );
   sigaction( SIGILL,  &sa, NULL );
   sigaction( SIGFPE,  &sa, NULL );
   sigaction( SIGPIPE, &sa, NULL );

	//TODO:
	// - Block editing: press ' ' to remove blocks near player
	// - After above, encapsulate game logic
	gl::init();

	gl::Window window;
//	glfwWindowHint(GLFW_SAMPLES,100);
	window.setMajorVersion(4);
	window.setMinorVersion(5);
	window.create();
	window.setTitle("YAGL Minecraft #1");
	window.setSize(1000,1000);
	glfwSetWindowPos(window.ptr,10,10);
	window.bind();

	Game game;
	game.init();
	window.hideMouse();

	window.unbind();

	while(window.isOpen()){

		window.bind();

		game.loop(window);

		window.clearInputs();
		window.updateSize();
		window.unbind();
	}

	gl::end();
	return 0;
}
