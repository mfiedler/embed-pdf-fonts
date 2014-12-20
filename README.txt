	      ___________________________________________

			    EMBED-PDF-FONTS

	       Michael Fiedler <dev@michael-fiedler.net>
	      ___________________________________________


Table of Contents
_________________

1 Description
2 Usage
3 Dependencies
4 Installation
5 License
6 Contact





1 Description
=============

  `embed-pdf-fonts' embeds fonts referenced from an existing PDF
  document as a font subset, following [Fontconfig] font substitution
  settings.

  If all fonts referenced from a PDF file are embedded, the display
  quality of the document will not depend on the availability of the
  used fonts at the viewer's computer any more.  Moreover, Fontconfig
  settings such as font substitutions are respected during processing.
  This way, fonts that are not available on a system and cause display
  problems for an existing PDF document can be replaced so the problem
  does not occur any more on other systems missing the referenced fonts,
  too.  If a font is fully embedded in the input PDF, it will be reduced
  to the subset of used symbols, reducing file size.

  Note: It is also possible to use Poppler utilities for this purpose
  (`pdftocairo').


  [Fontconfig] http://www.freedesktop.org/wiki/Software/fontconfig/


2 Usage
=======

  ,----
  | embed-pdf-fonts input.pdf output.pdf
  `----


3 Dependencies
==============

  - [Cairo]
  - [Poppler] (GLib interface)

  On a Debian-based Linux system, you can install these via

  ,----
  | sudo apt-get install libcairo2-dev libpoppler-glib-dev
  `----


  [Cairo] http://cairographics.org/

  [Poppler] http://poppler.freedesktop.org/


4 Installation
==============

  ,----
  | make
  | sudo make install
  `----


5 License
=========

  This project is released under the terms of the GNU General Public
  License version 3 or later.  See the file `LICENSE_GPL-3' for the full
  license text.


6 Contact
=========

  File a new issue at
  [https://github.com/mfiedler/embed-pdf-fonts/issues] or write an email
  to `dev %AT% michael-fiedler %DOT% net'
