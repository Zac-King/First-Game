For the Assignment:
	  When you run the program, you'll now hit breakpoints.
	  Go through each breakpoint and write a comment in the code.
	  The comment should describe, as briefly as possible, what is going on.
	  Research some of the existing files to see what sort of detail 
	  the comments should have.



Project Overview:

Take a look at each file to get an idea of what's going on. Start at the main, try not
to be intimidated. It's not really any different from reading a book. The program already works-
you just need to remove breakpoints and put some comments in to show me that you have an idea of
what is going on.

	Decl.h:
		Decl contains Declarations. This allows for any file that includes it
		to define pointers without having to know anything about the classes
		themselves. A pointer is only 4-bytes, regardless of the Type! So it
		doesn't matter if we know what the class is or does. It only matters
		if we de-reference it.

	Assets:
		A class to manage the automatic deletion of sprites
		from memory. It's always a good idea to let a single
		object manage the loading and unloading of art assets.

		That way you don't accidentally load the same asset twice!

	GameState:
		In this case, GameState manages the Player and the Bullets.
		It's not full-featured or anything, but it allows the Player
		to tell the GameState to spawn a bullet.

		Look closely at how the Bullet spawning works!

	Player:
		Player isn't really any different from what we've already talked
		about. So you'll find that it is more heavily commented.
		The main difference is that it has a pointer to a GameState,
		allowing the Player to call the public functions of the GameState.

		This lets it tell the GameState to spawn bullets!

	Bullet:
		Bullet is practically no different from the Player. It provides a way
		to communicate to the GameState whether or not it's ready to be
		deleted and removed from memory.
