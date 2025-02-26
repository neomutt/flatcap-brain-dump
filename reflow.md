# Reflowing Windows

The screen is divided into a set of nested Windows.
Besides the visible Windows, like the Index panel or the Sidebar, there are some
invisible containers that constrain the layout.  Containers are also Windows.

- **(V)**ertical containers: The children use a fixed amount of vertical space,
  but fill the available horizontal space.

- **(H)**orizontal containers: The children use a fixed amount of horizontal space,
  but fill the available vertical space.

The size of each Window can be Fixed, Maximised or Minimised.

- **Fixed**: The Window must be exactly this size
- **Maximise**: Use all the available space in the container
- **Minimise**: Calculate the size required by the children

Finally, a Window may be **Hidden**.  Hidden Windows take up no space.

## Layout

To lay out the Windows, we start with the Root Window which is the size of the
terminal screen.  It's a Vertical window, so we're allocating vertical space.

We iterate through its immediate children.

- A **Fixed** Window must be given the space it wants (if available).

- A **Maximise** Window will be given 1 row of space, for now.
  We keep a count of Maximised Windows.

- A **Minimise** Window is trickier.  We must run the layout on its children first.
  When we have a size for them, the Minimised Window will be treated as if it were a Fixed size.

When the children have been processed we shared any remaining space amongst the
Maximised Windows, if there are any, adjusting the Window positions as necessary.

Now each child Window has a size, we recurse through all their children.

