rng
===

.. contents::
   :local:

Description
-----------

``rng`` streams input from a file or ``stdin`` to ``stdout``.

It is the love child of ``sed -n '<START>,<END>p'`` and ``tail -n``.

Installation
------------

You can install ``rng`` via Homebrew or manually.

Homebrew
^^^^^^^^

.. code-block:: sh

   brew tap nickolasburr/pfa
   brew install rng

Source
^^^^^^

.. code-block:: sh

   git clone https://github.com/nickolasburr/rng.git
   cd rng
   make
   make install

By default, files are installed to ``/usr/local`` You can install elsewhere by passing ``PREFIX`` to ``make install``.

.. code-block:: sh

   make install PREFIX=/opt

Notes
-----

Certain range values can be omitted if they can be properly implied. To get multiple ranges, use the colon (``:``) operator.

Examples
--------

Get lines 7-15 in ``Makefile``.

.. code-block:: sh

   rng 7,15 Makefile

Skip the first 4 lines of input from a pipe.

.. code-block:: sh

   echo -e "First\nSecond\nThird\nFourth\nFifth" | rng 5

Output lines 1-25 in ``Makefile``.

.. code-block:: sh

   rng ,25 Makefile

Get lines 5-10 and 17-22 in ``main.c``.

.. code-block:: sh

   rng 5,10:17,22 main.c

Output all lines except 11-19 in main.c

.. code-block:: sh

   rng ,10:20, main.c

Get lines 16-27 of a text document from the web.

.. code-block:: sh

   curl -fsL https://www.w3.org/TR/2003/REC-PNG-20031110/iso_8859-1.txt | rng 16,27
