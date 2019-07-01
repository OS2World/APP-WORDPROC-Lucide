:userdoc.
:docprof toc=123456.
:title.Lucide User's Guide
.* rev 2016-10-17-001
.* rev 2018-12-03-002
.* ----------------------------------------------------------------------------
:h1 res=001 name=intro
    x=left y=bottom width=100% height=100%.About Lucide
:artwork align=center name='lucidelogo.bmp'.
:hp2.Lucide:ehp2. is a plugin-based document viewer with support for various
file formats, primarily, Adobe's Portable Document Format (PDF). It provides
a SOM-based plugin architecture which allows third-party developers to easily
add plugins to support additional file formats.


:p.:ul compact.
:li.:link reftype=hd res=002.License:elink.
:li.:link reftype=hd res=003.Acknowledgments:elink.
:li.:link reftype=hd res=004.Program start:elink.
:li.:link reftype=hd res=1005.Language support:elink.
:li.:link reftype=hd res=005.Interface:elink.
:li.:link reftype=hd res=006.Panes:elink.
:li.:link reftype=hd res=020.Toolbar:elink.
:li.:link reftype=hd res=100.Dialogs &amp. Listboxes:elink.
:li.:link reftype=hd res=200.Menus:elink.
:li.:link reftype=hd res=400.Keyboard accelerators:elink.
:li.:link reftype=hd res=500.How do I...:elink.
:li.:link reftype=hd res=700.Concepts:elink.
:li.:link reftype=hd res=800.Approach:elink.
:li.:link reftype=hd res=900.References:elink.
:li.:link reftype=hd res=950.Notices:elink.
:li.:link reftype=hd res=960.Appendix:elink.
:eul.
:p.

.* ............................................................................
:h2 res=002 name=license
    x=left y=bottom width=100% height=100%.License

:hp2.Lucide:ehp2. is dual licensed under the COMMON DEVELOPMENT AND
DISTRIBUTION LICENSE (CDDL) Version 1.0 and the GNU LESSER GENERAL PUBLIC
LICENSE Version 2.1.

:p.Plugins for :hp2.Lucide:ehp2. are released under CDDL/LGPL or GPL,
depending upon the plugin. See https&colon.//trac.netlabs.org/lucide/
for more information and source code.
:p.

.ce COMMON DEVELOPMENT AND DISTRIBUTION LICENSE (CDDL) Version 1.0
.br
:p.1. Definitions.

:p.1.1. Contributor means each individual or entity that creates or
contributes to the creation of Modifications.

:p.1.2. Contributor Version means the combination of the Original
Software, prior Modifications used by a Contributor (if any),
and the Modifications made by that particular Contributor.

:p.1.3. Covered Software means (a) the Original Software, or (b)
Modifications, or (c) the combination of files containing
Original Software with files containing Modifications, in each
case including portions thereof.

:p.1.4. Executable means the Covered Software in any form other
than Source Code.

:p.1.5. Initial Developer means the individual or entity that first
makes Original Software available under this License.

:p.1.6. Larger Work means a work which combines Covered Software or
portions thereof with code not governed by the terms of this
License.

:p.1.7. License means this document.

:p.1.8. Licensable means having the right to grant, to the maximum
extent possible, whether at the time of the initial grant or 
subsequently acquired, any and all of the rights conveyed herein.

:p.1.9. Modifications means the Source Code and Executable form of
any of the following: A. Any file that results from an addition
to, deletion from or modification of the contents of a file
containing Original Software or previous Modifications; B. Any
new file that contains any part of the Original Software or
previous Modification; or C. Any new file that is contributed or
otherwise made available under the terms of this License.

:p.1.10. Original Software means the Source Code and Executable
form of computer software code that is originally released under
this License.

:p.1.11. Patent Claims means any patent claim(s), now owned or
hereafter acquired, including without limitation, method,
process, and apparatus claims, in any patent Licensable by
grantor.

:p.1.12. Source Code means (a) the common form of computer software
code in which modifications are made and (b) associated
documentation included in or with such code.

:p.1.13. You (or Your) means an individual or a legal entity
exercising rights under, and complying with all of the terms of,
this License. For legal entities, You includes any entity which
controls, is controlled by, or is under common control with You.
For purposes of this definition, control means (a) the power,
direct or indirect, to cause the direction or management of such
entity, whether by contract or otherwise, or (b) ownership of
more than fifty percent (50%) of the outstanding shares or
beneficial ownership of such entity.

:p.2. License Grants.

:p.2.1. The Initial Developer Grant. Conditioned upon Your
compliance with Section 3.1 below and subject to third party
intellectual property claims, the Initial Developer hereby
grants You a world-wide, royalty-free, non-exclusive license:

:dl tsize=3 break=none.
:dt.(a)
:dd.under intellectual property rights (other than patent or
trademark) Licensable by Initial Developer, to use, reproduce,
modify, display, perform, sublicense and distribute the Original
Software (or portions thereof), with or without Modifications,
and/or as part of a Larger Work; and
:dt.(b)
:dd.under Patent Claims infringed by the making, using or
selling of Original Software, to make, have made, use, practice,
sell, and offer for sale, and/or otherwise dispose of the
Original Software (or portions thereof);
:dt.(c)
:dd.The licenses granted in Sections 2.1(a) and (b) are
effective on the date Initial Developer first distributes or
otherwise makes the Original Software available to a third party
under the terms of this License;
:dt.(d)
:dd.Notwithstanding Section 2.1(b) above, no patent license is
granted: (1) for code that You delete from the Original
Software, or (2) for infringements caused by: (i) the
modification of the Original Software, or (ii) the combination
of the Original Software with other software or devices.
:edl.

:p.2.2. Contributor Grant. Conditioned upon Your compliance with
Section 3.1 below and subject to third party intellectual
property claims, each Contributor hereby grants You a
world-wide, royalty-free, non-exclusive license:

:dl tsize=3 break=none.
:dt.(a)
:dd.under intellectual property rights (other than patent or
trademark) Licensable by Contributor to use, reproduce, modify,
display, perform, sublicense and distribute the Modifications
created by such Contributor (or portions thereof), either on an
unmodified basis, with other Modifications, as Covered Software
and/or as part of a Larger Work; and
:dt.(b)
:dd.under Patent Claims infringed by the making, using, or
selling of Modifications made by that Contributor either alone
and/or in combination with its Contributor Version (or portions
of such combination), to make, use, sell, offer for sale, have
made, and/or otherwise dispose of: (1) Modifications made by
that Contributor (or portions thereof); and (2) the combination
of Modifications made by that Contributor with its Contributor
Version (or portions of such combination).
:dt.(c)
:dd.The licenses granted in Sections 2.2(a) and 2.2(b)
are effective on the date Contributor first distributes or
otherwise makes the Modifications available to a third party.
:dt.(d)
:dd.Notwithstanding Section 2.2(b) above, no patent license is
granted: (1) for any code that Contributor has deleted from the
Contributor Version; (2) for infringements caused by: (i) third
party modifications of Contributor Version, or (ii) the
combination of Modifications made by that Contributor with other
software (except as part of the Contributor Version) or other
devices; or (3) under Patent Claims infringed by Covered
Software in the absence of Modifications made by that
Contributor.
:edl.

:p.3. Distribution Obligations.

:p.3.1. Availability of Source Code. Any Covered Software that You
distribute or otherwise make available in Executable form must
also be made available in Source Code form and that Source Code
form must be distributed only under the terms of this License.
You must include a copy of this License with every copy of the
Source Code form of the Covered Software You distribute or
otherwise make available. You must inform recipients of any such
Covered Software in Executable form as to how they can obtain
such Covered Software in Source Code form in a reasonable manner
on or through a medium customarily used for software exchange.

:p.3.2. Modifications. The Modifications that You create or to
which You contribute are governed by the terms of this License.
You represent that You believe Your Modifications are Your
original creation(s) and/or You have sufficient rights to grant
the rights conveyed by this License.

:p.3.3. Required Notices. You must include a notice in each of Your
Modifications that identifies You as the Contributor of the
Modification. You may not remove or alter any copyright, patent
or trademark notices contained within the Covered Software, or
any notices of licensing or any descriptive text giving
attribution to any Contributor or the Initial Developer.

:p.3.4. Application of Additional Terms. You may not offer or
impose any terms on any Covered Software in Source Code form
that alters or restricts the applicable version of this License
or the recipients rights hereunder. You may choose to offer, and
to charge a fee for, warranty, support, indemnity or liability
obligations to one or more recipients of Covered
Software. However, you may do so only on Your own behalf, and
not on behalf of the Initial Developer or any Contributor. You
must make it absolutely clear that any such warranty, support,
indemnity or liability obligation is offered by You alone, and
You hereby agree to indemnify the Initial Developer and every
Contributor for any liability incurred by the Initial Developer
or such Contributor as a result of warranty, support, indemnity
or liability terms You offer.

:p.3.5. Distribution of Executable Versions. You may distribute the
Executable form of the Covered Software under the terms of this
License or under the terms of a license of Your choice, which
may contain terms different from this License, provided that You
are in compliance with the terms of this License and that the
license for the Executable form does not attempt to limit or
alter the recipients rights in the Source Code form from the
rights set forth in this License. If You distribute the Covered
Software in Executable form under a different license, You must
make it absolutely clear that any terms which differ from this
License are offered by You alone, not by the Initial Developer
or Contributor. You hereby agree to indemnify the Initial
Developer and every Contributor for any liability incurred by
the Initial Developer or such Contributor as a result of any
such terms You offer.

:p.3.6. Larger Works. You may create a Larger Work by combining
Covered Software with other code not governed by the terms of
this License and distribute the Larger Work as a single product.
In such a case, You must make sure the requirements of this
License are fulfilled for the Covered Software.

:p.4. Versions of the License.

:p.4.1. New Versions. Sun Microsystems, Inc. is the initial license
steward and may publish revised and/or new versions of this
License from time to time. Each version will be given a
distinguishing version number. Except as provided in Section
:p.4.3, no one other than the license steward has the right to
modify this License.

:p.4.2. Effect of New Versions. You may always continue to use,
distribute or otherwise make the Covered Software available
under the terms of the version of the License under which You
originally received the Covered Software. If the Initial
Developer includes a notice in the Original Software prohibiting
it from being distributed or otherwise made available under any
subsequent version of the License, You must distribute and make
the Covered Software available under the terms of the version of
the License under which You originally received the Covered
Software.  Otherwise, You may also choose to use, distribute or
otherwise make the Covered Software available under the terms of
any subsequent version of the License published by the license
steward.

:p.4.3. Modified Versions. When You are an Initial Developer and
You want to create a new license for Your Original Software, You
may create and use a modified version of this License if You:
(a) rename the license and remove any references to the name of
the license steward (except to note that the license differs
from this License); and (b) otherwise make it clear that the
license contains terms which differ from this License.

:p.5. DISCLAIMER OF WARRANTY. COVERED SOFTWARE IS PROVIDED UNDER
THIS LICENSE ON AN AS IS BASIS, WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION,
WARRANTIES THAT THE COVERED SOFTWARE IS FREE OF DEFECTS,
MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE OR NON-INFRINGING.
THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
SOFTWARE IS WITH YOU. SHOULD ANY COVERED SOFTWARE PROVE
DEFECTIVE IN ANY RESPECT, YOU (NOT THE INITIAL DEVELOPER OR ANY
OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY SERVICING,
REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN
ESSENTIAL PART OF THIS LICENSE. NO USE OF ANY COVERED SOFTWARE
IS AUTHORIZED HEREUNDER EXCEPT UNDER THIS DISCLAIMER.

:p.6. TERMINATION.

:p.6.1. This License and the rights granted hereunder will
terminate automatically if You fail to comply with terms herein
and fail to cure such breach within 30 days of becoming aware of
the breach. Provisions which, by their nature, must remain in
effect beyond the termination of this License shall survive.

:p.6.2. If You assert a patent infringement claim (excluding
declaratory judgment actions) against Initial Developer or a
Contributor (the Initial Developer or Contributor against whom
You assert such claim is referred to as Participant) alleging
that the Participant Software (meaning the Contributor Version
where the Participant is a Contributor or the Original Software
where the Participant is the Initial Developer) directly or
indirectly infringes any patent, then any and all rights granted
directly or indirectly to You by such Participant, the Initial
Developer (if the Initial Developer is not the Participant) and
all Contributors under Sections 2.1 and/or 2.2 of this License
shall, upon 60 days notice from Participant terminate
prospectively and automatically at the expiration of such 60 day
notice period, unless if within such 60 day period You withdraw
Your claim with respect to the Participant Software against such
Participant either unilaterally or pursuant to a written
agreement with Participant.

:p.6.3. In the event of termination under Sections 6.1 or 6.2
above, all end user licenses that have been validly granted by
You or any distributor hereunder prior to termination (excluding
licenses granted to You by any distributor) shall survive
termination.

:p.7. LIMITATION OF LIABILITY. UNDER NO CIRCUMSTANCES AND UNDER NO
LEGAL THEORY, WHETHER TORT (INCLUDING NEGLIGENCE), CONTRACT, OR
OTHERWISE, SHALL YOU, THE INITIAL DEVELOPER, ANY OTHER
CONTRIBUTOR, OR ANY DISTRIBUTOR OF COVERED SOFTWARE, OR ANY
SUPPLIER OF ANY OF SUCH PARTIES, BE LIABLE TO ANY PERSON FOR ANY
INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES OF ANY
CHARACTER INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOST
PROFITS, LOSS OF GOODWILL, WORK STOPPAGE, COMPUTER FAILURE OR
MALFUNCTION, OR ANY AND ALL OTHER COMMERCIAL DAMAGES OR LOSSES,
EVEN IF SUCH PARTY SHALL HAVE BEEN INFORMED OF THE POSSIBILITY
OF SUCH DAMAGES. THIS LIMITATION OF LIABILITY SHALL NOT APPLY TO
LIABILITY FOR DEATH OR PERSONAL INJURY RESULTING FROM SUCH
PARTYS NEGLIGENCE TO THE EXTENT APPLICABLE LAW PROHIBITS SUCH
LIMITATION. SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR
LIMITATION OF INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THIS
EXCLUSION AND LIMITATION MAY NOT APPLY TO YOU.

:p.8. U.S. GOVERNMENT END USERS. The Covered Software is a
commercial item, as that term is defined in 48 C.F.R. 2.101
(Oct. 1995), consisting of commercial computer software (as that
term is defined at 48 C.F.R. 252.227-7014(a)(1)) and commercial
computer software documentation as such terms are used in 48
C.F.R. 12.212 (Sept. 1995). Consistent with 48 C.F.R. 12.212 and
48 C.F.R. 227.7202-1 through 227.7202-4 (June 1995), all
U.S. Government End Users acquire Covered Software with only
those rights set forth herein. This U.S. Government Rights
clause is in lieu of, and supersedes, any other FAR, DFAR, or
other clause or provision that addresses Government rights in
computer software under this License.

:p.9. MISCELLANEOUS. This License represents the complete agreement
concerning subject matter hereof. If any provision of this
License is held to be unenforceable, such provision shall be
reformed only to the extent necessary to make it enforceable.
This License shall be governed by the law of the jurisdiction
specified in a notice contained within the Original Software
(except to the extent applicable law, if any, provides
otherwise), excluding such jurisdictions conflict-of-law
provisions. Any litigation relating to this License shall be
subject to the jurisdiction of the courts located in the
jurisdiction and venue specified in a notice contained within
the Original Software, with the losing party responsible for
costs, including, without limitation, court costs and reasonable
attorneys fees and expenses. The application of the United
Nations Convention on Contracts for the International Sale of
Goods is expressly excluded. Any law or regulation which
provides that the language of a contract shall be construed
against the drafter shall not apply to this License. You agree
that You alone are responsible for compliance with the United
States export administration regulations (and the export control
laws and regulation of any other countries) when You use,
distribute or otherwise make available any Covered Software.

:p.10. RESPONSIBILITY FOR CLAIMS. As between Initial Developer and
the Contributors, each party is responsible for claims and
damages arising, directly or indirectly, out of its utilization
of rights under this License and You agree to work with Initial
Developer and Contributors to distribute such responsibility on
an equitable basis. Nothing herein is intended or shall be
deemed to constitute any admission of liability.

:p.----------------------------------------------------------------

:p.NOTICE PURSUANT TO SECTION 9 OF THE COMMON DEVELOPMENT AND
DISTRIBUTION LICENSE (CDDL): This code is released under the
CDDL and shall be governed by the laws of the State of
California (excluding conflict-of-law provisions). Any
litigation relating to this License shall be subject to the
jurisdiction of the Federal Courts of the Northern District of
California and the state courts of the State of California, with
venue lying in Santa Clara County, California.

:p.----------------------------------------------------------------
:p.

.ce GNU LESSER GENERAL PUBLIC LICENSE
.ce Version 2.1, February 1999
:p.
:p.Copyright (C) 1991, 1999 Free Software Foundation, Inc.
.br
51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
.br
Everyone is permitted to copy and distribute verbatim copies
of this license document, but changing it is not allowed.

:p.[This is the first released version of the Lesser GPL.  It also counts
as the successor of the GNU Library Public License, version 2, hence
the version number 2.1.]

.ce Preamble

:p.The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
Licenses are intended to guarantee your freedom to share and change
free software--to make sure the software is free for all its users.

:p.This license, the Lesser General Public License, applies to some
specially designated software packages--typically libraries--of the
Free Software Foundation and other authors who decide to use it.  You
can use it too, but we suggest you first think carefully about whether
this license or the ordinary General Public License is the better
strategy to use in any particular case, based on the explanations below.

:p.When we speak of free software, we are referring to freedom of use,
not price.  Our General Public Licenses are designed to make sure that
you have the freedom to distribute copies of free software (and charge
for this service if you wish); that you receive source code or can get
it if you want it; that you can change the software and use pieces of
it in new free programs; and that you are informed that you can do
these things.

:p.To protect your rights, we need to make restrictions that forbid
distributors to deny you these rights or to ask you to surrender these
rights.  These restrictions translate to certain responsibilities for
you if you distribute copies of the library or if you modify it.

:p.For example, if you distribute copies of the library, whether gratis
or for a fee, you must give the recipients all the rights that we gave
you.  You must make sure that they, too, receive or can get the source
code.  If you link other code with the library, you must provide
complete object files to the recipients, so that they can relink them
with the library after making changes to the library and recompiling
it.  And you must show them these terms so they know their rights.

:p.We protect your rights with a two-step method: (1) we copyright the
library, and (2) we offer you this license, which gives you legal
permission to copy, distribute and/or modify the library.

:p.To protect each distributor, we want to make it very clear that
there is no warranty for the free library.  Also, if the library is
modified by someone else and passed on, the recipients should know
that what they have is not the original version, so that the original
author's reputation will not be affected by problems that might be
introduced by others.

:p.Finally, software patents pose a constant threat to the existence of
any free program.  We wish to make sure that a company cannot
effectively restrict the users of a free program by obtaining a
restrictive license from a patent holder.  Therefore, we insist that
any patent license obtained for a version of the library must be
consistent with the full freedom of use specified in this license.

:p.Most GNU software, including some libraries, is covered by the
ordinary GNU General Public License.  This license, the GNU Lesser
General Public License, applies to certain designated libraries, and
is quite different from the ordinary General Public License.  We use
this license for certain libraries in order to permit linking those
libraries into non-free programs.

:p.When a program is linked with a library, whether statically or using
a shared library, the combination of the two is legally speaking a
combined work, a derivative of the original library.  The ordinary
General Public License therefore permits such linking only if the
entire combination fits its criteria of freedom.  The Lesser General
Public License permits more lax criteria for linking other code with
the library.

:p.We call this license the "Lesser" General Public License because it
does Less to protect the user's freedom than the ordinary General
Public License.  It also provides other free software developers Less
of an advantage over competing non-free programs.  These disadvantages
are the reason we use the ordinary General Public License for many
libraries.  However, the Lesser license provides advantages in certain
special circumstances.

:p.For example, on rare occasions, there may be a special need to
encourage the widest possible use of a certain library, so that it becomes
a de-facto standard.  To achieve this, non-free programs must be
allowed to use the library.  A more frequent case is that a free
library does the same job as widely used non-free libraries.  In this
case, there is little to gain by limiting the free library to free
software only, so we use the Lesser General Public License.

:p.In other cases, permission to use a particular library in non-free
programs enables a greater number of people to use a large body of
free software.  For example, permission to use the GNU C Library in
non-free programs enables many more people to use the whole GNU
operating system, as well as its variant, the GNU/Linux operating
system.

:p.Although the Lesser General Public License is Less protective of the
users' freedom, it does ensure that the user of a program that is
linked with the Library has the freedom and the wherewithal to run
that program using a modified version of the Library.

:p.The precise terms and conditions for copying, distribution and
modification follow.  Pay close attention to the difference between a
"work based on the library" and a "work that uses the library".  The
former contains code derived from the library, whereas the latter must
be combined with the library in order to run.
:p.

.ce GNU LESSER GENERAL PUBLIC LICENSE
.ce TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

:p.0. This License Agreement applies to any software library or other
program which contains a notice placed by the copyright holder or
other authorized party saying it may be distributed under the terms of
this Lesser General Public License (also called "this License").
Each licensee is addressed as "you".

:p.A "library" means a collection of software functions and/or data
prepared so as to be conveniently linked with application programs
(which use some of those functions and data) to form executables.

:p.The "Library", below, refers to any such software library or work
which has been distributed under these terms.  A "work based on the
Library" means either the Library or any derivative work under
copyright law: that is to say, a work containing the Library or a
portion of it, either verbatim or with modifications and/or translated
straightforwardly into another language.  (Hereinafter, translation is
included without limitation in the term "modification".)

:p."Source code" for a work means the preferred form of the work for
making modifications to it.  For a library, complete source code means
all the source code for all modules it contains, plus any associated
interface definition files, plus the scripts used to control compilation
and installation of the library.

:p.Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running a program using the Library is not restricted, and output from
such a program is covered only if its contents constitute a work based
on the Library (independent of the use of the Library in a tool for
writing it).  Whether that is true depends on what the Library does
and what the program that uses the Library does.
  
:p.1. You may copy and distribute verbatim copies of the Library's
complete source code as you receive it, in any medium, provided that
you conspicuously and appropriately publish on each copy an
appropriate copyright notice and disclaimer of warranty; keep intact
all the notices that refer to this License and to the absence of any
warranty; and distribute a copy of this License along with the
Library.

:p.You may charge a fee for the physical act of transferring a copy,
and you may at your option offer warranty protection in exchange for a
fee.

:p.2. You may modify your copy or copies of the Library or any portion
of it, thus forming a work based on the Library, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions:

:dl tsize=3 break=none.
:dt.a)
:dd.The modified work must itself be a software library.
:dt.b)
:dd.You must cause the files modified to carry prominent notices
stating that you changed the files and the date of any change.
:dt.c)
:dd.You must cause the whole of the work to be licensed at no
charge to all third parties under the terms of this License.
:dt.(d)
:dd.If a facility in the modified Library refers to a function or a
table of data to be supplied by an application program that uses
the facility, other than as an argument passed when the facility
is invoked, then you must make a good faith effort to ensure that,
in the event an application does not supply such function or
table, the facility still operates, and performs whatever part of
its purpose remains meaningful.
:edl.

:p.(For example, a function in a library to compute square roots has
a purpose that is entirely well-defined independent of the
application.  Therefore, Subsection 2d requires that any
application-supplied function or table used by this function must
be optional: if the application does not supply it, the square
root function must still compute square roots.)

:p.These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Library,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Library, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote
it.

:p.Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Library.

:p.In addition, mere aggregation of another work not based on the Library
with the Library (or with a work based on the Library) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

:p.3. You may opt to apply the terms of the ordinary GNU General Public
License instead of this License to a given copy of the Library.  To do
this, you must alter all the notices that refer to this License, so
that they refer to the ordinary GNU General Public License, version 2,
instead of to this License.  (If a newer version than version 2 of the
ordinary GNU General Public License has appeared, then you can specify
that version instead if you wish.)  Do not make any other change in
these notices.

:p.Once this change is made in a given copy, it is irreversible for
that copy, so the ordinary GNU General Public License applies to all
subsequent copies and derivative works made from that copy.

:p.This option is useful when you wish to copy part of the code of
the Library into a program that is not a library.

:p.4. You may copy and distribute the Library (or a portion or
derivative of it, under Section 2) in object code or executable form
under the terms of Sections 1 and 2 above provided that you accompany
it with the complete corresponding machine-readable source code, which
must be distributed under the terms of Sections 1 and 2 above on a
medium customarily used for software interchange.

:p.If distribution of object code is made by offering access to copy
from a designated place, then offering equivalent access to copy the
source code from the same place satisfies the requirement to
distribute the source code, even though third parties are not
compelled to copy the source along with the object code.

:p.5. A program that contains no derivative of any portion of the
Library, but is designed to work with the Library by being compiled or
linked with it, is called a "work that uses the Library".  Such a
work, in isolation, is not a derivative work of the Library, and
therefore falls outside the scope of this License.

:p.However, linking a "work that uses the Library" with the Library
creates an executable that is a derivative of the Library (because it
contains portions of the Library), rather than a "work that uses the
library".  The executable is therefore covered by this License.
Section 6 states terms for distribution of such executables.

:p.When a "work that uses the Library" uses material from a header file
that is part of the Library, the object code for the work may be a
derivative work of the Library even though the source code is not.
Whether this is true is especially significant if the work can be
linked without the Library, or if the work is itself a library.  The
threshold for this to be true is not precisely defined by law.

:p.If such an object file uses only numerical parameters, data
structure layouts and accessors, and small macros and small inline
functions (ten lines or less in length), then the use of the object
file is unrestricted, regardless of whether it is legally a derivative
work.  (Executables containing this object code plus portions of the
Library will still fall under Section 6.)

:p.Otherwise, if the work is a derivative of the Library, you may
distribute the object code for the work under the terms of Section 6.
Any executables containing that work also fall under Section 6,
whether or not they are linked directly with the Library itself.

:p.6. As an exception to the Sections above, you may also combine or
link a "work that uses the Library" with the Library to produce a
work containing portions of the Library, and distribute that work
under terms of your choice, provided that the terms permit
modification of the work for the customer's own use and reverse
engineering for debugging such modifications.

:p.You must give prominent notice with each copy of the work that the
Library is used in it and that the Library and its use are covered by
this License.  You must supply a copy of this License.  If the work
during execution displays copyright notices, you must include the
copyright notice for the Library among them, as well as a reference
directing the user to the copy of this License.  Also, you must do one
of these things:

:dl tsize=3 break=none.
:dt.a)
:dd.Accompany the work with the complete corresponding
machine-readable source code for the Library including whatever
changes were used in the work (which must be distributed under
Sections 1 and 2 above); and, if the work is an executable linked
with the Library, with the complete machine-readable "work that
uses the Library", as object code and/or source code, so that the
user can modify the Library and then relink to produce a modified
executable containing the modified Library.  (It is understood
that the user who changes the contents of definitions files in the
Library will not necessarily be able to recompile the application
to use the modified definitions.)
:dt.b)
:dd.Use a suitable shared library mechanism for linking with the
Library.  A suitable mechanism is one that (1) uses at run time a
copy of the library already present on the user's computer system,
rather than copying library functions into the executable, and (2)
will operate properly with a modified version of the library, if
the user installs one, as long as the modified version is
interface-compatible with the version that the work was made with.
:dt.c)
:dd.Accompany the work with a written offer, valid for at
least three years, to give the same user the materials
specified in Subsection 6a, above, for a charge no more
than the cost of performing this distribution.
:dt.d)
:dd.If distribution of the work is made by offering access to copy
from a designated place, offer equivalent access to copy the above
specified materials from the same place.
:dt.e)
:dd.Verify that the user has already received a copy of these
materials or that you have already sent this user a copy.
:edl.

:p.For an executable, the required form of the "work that uses the
Library" must include any data and utility programs needed for
reproducing the executable from it.  However, as a special exception,
the materials to be distributed need not include anything that is
normally distributed (in either source or binary form) with the major
components (compiler, kernel, and so on) of the operating system on
which the executable runs, unless that component itself accompanies
the executable.

:p.It may happen that this requirement contradicts the license
restrictions of other proprietary libraries that do not normally
accompany the operating system.  Such a contradiction means you cannot
use both them and the Library together in an executable that you
distribute.

:p.7. You may place library facilities that are a work based on the
Library side-by-side in a single library together with other library
facilities not covered by this License, and distribute such a combined
library, provided that the separate distribution of the work based on
the Library and of the other library facilities is otherwise
permitted, and provided that you do these two things:

:dl tsize=3 break=none.
:dt.a)
:dd.Accompany the combined library with a copy of the same work
based on the Library, uncombined with any other library
facilities.  This must be distributed under the terms of the
Sections above.
:dt.b)
:dd.Give prominent notice with the combined library of the fact
that part of it is a work based on the Library, and explaining
where to find the accompanying uncombined form of the same work.
:edl.

:p.8. You may not copy, modify, sublicense, link with, or distribute
the Library except as expressly provided under this License.  Any
attempt otherwise to copy, modify, sublicense, link with, or
distribute the Library is void, and will automatically terminate your
rights under this License.  However, parties who have received copies,
or rights, from you under this License will not have their licenses
terminated so long as such parties remain in full compliance.

:p.9. You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Library or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Library (or any work based on the
Library), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Library or works based on it.

:p.10. Each time you redistribute the Library (or any work based on the
Library), the recipient automatically receives a license from the
original licensor to copy, distribute, link with or modify the Library
subject to these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties with
this License.

:p.11. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Library at all.  For example, if a patent
license would not permit royalty-free redistribution of the Library by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Library.

:p.If any portion of this section is held invalid or unenforceable under any
particular circumstance, the balance of the section is intended to apply,
and the section as a whole is intended to apply in other circumstances.

:p.It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.

:p.This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.

:p.12. If the distribution and/or use of the Library is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Library under this License may add
an explicit geographical distribution limitation excluding those countries,
so that distribution is permitted only in or among countries not thus
excluded.  In such case, this License incorporates the limitation as if
written in the body of this License.

:p.13. The Free Software Foundation may publish revised and/or new
versions of the Lesser General Public License from time to time.
Such new versions will be similar in spirit to the present version,
but may differ in detail to address new problems or concerns.

:p.Each version is given a distinguishing version number.  If the Library
specifies a version number of this License which applies to it and
"any later version", you have the option of following the terms and
conditions either of that version or of any later version published by
the Free Software Foundation.  If the Library does not specify a
license version number, you may choose any version ever published by
the Free Software Foundation.

:p.14. If you wish to incorporate parts of the Library into other free
programs whose distribution conditions are incompatible with these,
write to the author to ask for permission.  For software which is
copyrighted by the Free Software Foundation, write to the Free
Software Foundation; we sometimes make exceptions for this.  Our
decision will be guided by the two goals of preserving the free status
of all derivatives of our free software and of promoting the sharing
and reuse of software generally.
:p.
.ce NO WARRANTY

:p.15. BECAUSE THE LIBRARY IS LICENSED FREE OF CHARGE, THERE IS NO
WARRANTY FOR THE LIBRARY, TO THE EXTENT PERMITTED BY APPLICABLE LAW.
EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR
OTHER PARTIES PROVIDE THE LIBRARY "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
LIBRARY IS WITH YOU.  SHOULD THE LIBRARY PROVE DEFECTIVE, YOU ASSUME
THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.

:p.16. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN
WRITING WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY
AND/OR REDISTRIBUTE THE LIBRARY AS PERMITTED ABOVE, BE LIABLE TO YOU
FOR DAMAGES, INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE
LIBRARY (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING
RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES OR A
FAILURE OF THE LIBRARY TO OPERATE WITH ANY OTHER SOFTWARE), EVEN IF
SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
DAMAGES.
:p.
.ce END OF TERMS AND CONDITIONS
:p.
.ce How to Apply These Terms to Your New Libraries

:p.If you develop a new library, and you want it to be of the greatest
possible use to the public, we recommend making it free software that
everyone can redistribute and change.  You can do so by permitting
redistribution under these terms (or, alternatively, under the terms of the
ordinary General Public License).

:p.To apply these terms, attach the following notices to the library.  It is
safest to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least the
"copyright" line and a pointer to where the full notice is found.

:xmp.
    &lt.one line to give the library's name and a brief idea of what it does.&gt.
    Copyright (C) &lt.year&gt.  &lt.name of author&gt.

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
:exmp.

:p.Also add information on how to contact you by electronic and paper mail.

:p.You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the library, if
necessary.  Here is a sample; alter the names:

:xmp.
  Yoyodyne, Inc., hereby disclaims all copyright interest in the
  library `Frob' (a library for tweaking knobs) written by James Random Hacker.

  &lt.signature of Ty Coon&gt., 1 April 1990
  Ty Coon, President of Vice
:exmp.

:p.That's all there is to it!


.* ............................................................................
:h2 res=003 name=credits
    x=left y=bottom width=100% height=100%.Acknowledgments
:p.Lucide is written and maintained by&colon.

:xmp.
    Eugene Romanenko, netlabs.org
    Dmitriy Kuminov, netlabs.org
    in cooperation with Serenity Systems International
    
    Gregg Young
    Andy Willis
    Steven Levine
    Matthias Waltenberger
    Ronald Brill
    Lewis Rosenthal
    a team of translators and contributors
    in cooperation with Arca Noae, LLC
:exmp.
:p.


.* ----------------------------------------------------------------------------
:h1 res=004 name=program_start
    x=left y=bottom width=100% height=100%.Program start

:p.Lucide may be started from the WPS object, either by itself, by dragging a
supported file type and dropping it on the object, or from the command line,
either by specifying the program name alone or by following it with the name of
a supported document to open.

:dl tsize=10 break=none.
:dt.:hp2.Example:ehp2.
:dd.:hp2.[C&colon.\PROGRAMS\Lucide]Lucide c&colon.\home\mydoc.pdf:ehp2.
:edl.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=228.Exit:elink.
:edl.

.* ----------------------------------------------------------------------------
:h1 res=1005 name=language_support
    x=left y=bottom width=100% height=100%.Language support
    
:p.Lucide supports 12 languages to varying degrees. The installer
installs only the language defined by the LANG environment variable
which is SET in config.sys. It installs English for unsupported languages.

:p.If you install multiple language packs Lucide will load the language
found in the LANG variable if it was installed. It will fall back to 
English (Lucide.lng) if it was installed. Finally it will search for any 
Lucide_xx.lng file which is installed in the following order de es fr it
sv da nl ru pl cs and zh loading the first one it finds. You can use any
supported language on any system by "only" installing that language.
Lucide 1.40 installed English by default so you should uninstall it first
or plan on deleting Lucide.lng if you wish to use a language other than
English or the system language.

:p. Do to the lack of current translations for everything but Spanish 
(German is the next most complete) the English help, GBM help, readme,
LUGBM readme, changelog and lugbm.cfg are installed. The translated 
lugbm_xx.cfg files are load before lugbm.cfg if one if found. If 
multiple lugbm_xx.cfg are installed the first one found based on the
order above is loaded.

.* ----------------------------------------------------------------------------
:h1 res=005 name=interface
    x=left y=bottom width=100% height=100%.Interface

:p.The application is designed with a one or two-pane display, with the
:link reftype=hd res=007.Navigation pane:elink. on the left providing a list of
clickable bookmarks for easy movement from one place or page to another, and
the :link reftype=hd res=008.Document pane:elink. on the right, providing a
scalable and scrollable window for the main file content.

:p.Between the :link reftype=hd res=007.Navigation pane:elink. and the :link
reftype=hd res=008.Document pane:elink. is a movable divider, or splitbar,
which also serves as the location for the :link reftype=hd res=007.Navigation
pane:elink. scrollbar, when needed. Dragging the splitbar left or right will set
its position for the remainder of the :hp2.Lucide:ehp2. session. Closing the
last :hp2.Lucide:ehp2. window in the current session will save the position of
the splitbar. Finally, new :hp2.Lucide:ehp2. windows opened from the :link
reftype=hd res=212.New window:elink. selection on the :link reftype=hd
res=210.Document menu:elink. will inherit the position of the splitbar from the
current window.

:p.The :link reftype=hd res=200.menu:elink. provides general navigation, and
some functions which are not available through the  
:link reftype=hd res=211.context menu:elink. or buttons.

:p.The final component of the user interface is the :link reftype=hd res=020.
Toolbar:elink., which provides some shortcuts to common functions and a current
view dropdown selector.

:p.:ul compact.
:li.:link reftype=hd res=006.Panes:elink.
:li.:link reftype=hd res=007.Navigation pane:elink.
:li.:link reftype=hd res=008.Document pane:elink.
:li.:link reftype=hd res=020.Toolbar:elink.
:li.:link reftype=hd res=100.Dialogs &amp. Listboxes:elink.
:li.:link reftype=hd res=200.Menus:elink.
:li.:link reftype=hd res=400.Keyboard accelerators:elink.
:eul.
:p.


.* ............................................................................
:h2 res=006 name=panes
    x=left y=bottom width=100% height=100%.Panes

:p.The :link reftype=hd res=007.Navigation pane:elink. is visible on the left,
providing a list of clickable bookmarks for easy movement from one place or
page to another. It may be toggled on or off via the :link reftype=hd res=400.
F9 Keyboard accelerator:elink., the toolbar button
:artwork runin name='navpanel.bmp'.
:artlink.
:link reftype=hd res=020.
:eartlink.
, or via the Window menu. When toggled off, the :link reftype=hd
res=008.Document pane:elink. is widened to fill the program window.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=007.Navigation pane:elink.
.br
:link reftype=hd res=008.Document pane:elink.
.br
:link reftype=hd res=020.Toolbar:elink.
:edl.


.* ............................................................................
:h3 res=007 name=nav_pane
    x=left y=bottom width=100% height=100%.Navigation pane

:p.The Navigation pane displays either configured bookmarks (as created with
a supported document) or a list of pages. Bookmarks may appear nested, with
expand :artwork runin name='expand.bmp'. and collapse :artwork runin
name='collapse.bmp'. buttons.

:p.For documents which have not had any bookmarks set, the Navigation pane will
display :hp2.Page 1:ehp2., :hp2.Page 2:ehp2., etc. Simply click on the desired
page to jump to it.

:p.The Navigation pane may be toggled on and off via any of the following&colon.

:p.:ul compact.
:li.:link reftype=hd res=302.Show navigation pane (Window menu option):elink.
:li.:link reftype=hd res=026.Show/hide navigation pane:elink.
:li.:link reftype=hd res=400.F9 Keyboard accelerator:elink.
:eul.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=200.Menus:elink.
.br
:link reftype=hd res=008.Document pane:elink.
:edl.


.* ............................................................................
:h3 res=008 name=document_pane
    x=left y=bottom width=100% height=100%.Document pane

:p.The Document pane displays the selected file. The document (or image,
depending upon the type of file currently loaded) may be :link reftype=hd
res=030.scaled:elink., :link reftype=hd res=280.rotated 90&deg. clockwise
:elink., :link reftype=hd res=281.rotated 90&deg. counter-clockwise:elink., 
:link reftype=hd res=034.zoomed in or out:elink., or :link reftype=hd res=303.
shown full screen:elink. or :link reftype=hd res=304.in presentation mode
:elink..

:p.The Document pane also allows for manual movement of the displayed
section by dragging the right mouse button, which cases the pointer to change
to the positioning hand :artwork runin name='hand_closed.bmp'. .

:p.Hyperlinks in documents generally appear in a contrasting color (blue, in
the case of PDFs, but other plugins may use other colors) and when the mouse is
hovering over one, the pointer changes to a hand :artwork runin
name='hand.bmp'. . Hyperlinks may reference other parts of the same document,
other documents, or may open external programs (such as for sending email or
visiting a website).

:p.Supported documents may be viewed not only by passing the filename on the
command line or from the :link reftype=hd res=102.Open File dialog:elink., but
also by dragging and dropping the file in the Document pane.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=200.Menus:elink.
.br
:link reftype=hd res=007.Navigation pane:elink.
.br
:link reftype=hd res=510.Opening hyperlinks:elink.
.br
:link reftype=hd res=740.PDF hyperlinks:elink.
:edl.


.* ............................................................................
:h2 res=020 name=toolbar
    x=left y=bottom width=100% height=100%.Toolbar

:p.The Toolbar offers access to some commonly-used features of Lucide&colon.

:p.:ul compact.
:li.:link reftype=hd res=022.Open document button:elink.
:li.:link reftype=hd res=024.Print button:elink.
:li.:link reftype=hd res=026.Show/hide navigation pane button:elink.
:li.:link reftype=hd res=028.Navigation controls:elink.
:li.:link reftype=hd res=030.Scaling controls:elink.
:li.:link reftype=hd res=032.Find button:elink.
:li.:link reftype=hd res=034.Zoom tool:elink.
:eul.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=200.Menus:elink.
.br
:link reftype=hd res=100.Dialogs &amp. Listboxes:elink.
:edl.


.* ............................................................................
:h3 res=022 name=open_document_button
    x=left y=bottom width=100% height=100%.Open document button

:p.The Open document toolbar button
:artwork runin name='open.bmp'.
:artlink.
:link reftype=hd res=102.
:eartlink.
accesses the :link reftype=hd res=102.Open File dialog:elink..


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.


.* ............................................................................
:h3 res=024 name=print_button
    x=left y=bottom width=100% height=100%.Print...

:p.The Print... toolbar button
:artwork runin name='print.bmp'.
:artlink.
:link reftype=hd res=104.
:eartlink.
accesses the :link reftype=hd res=104.Print dialog:elink..


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=224.Print...:elink.
.br
:link reftype=hd res=104.Print dialog:elink.
:edl.


.* ............................................................................
:h3 res=026 name=nav_pane_button
    x=left y=bottom width=100% height=100%.Show/hide navigation pane

:p.The Show/hide navigation pane toolbar button :artwork runin
name='navpanel.bmp'. toggles the :link reftype=hd res=007.Navigation
pane:elink..


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=007.Navigation pane:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
:edl.


.* ............................................................................
:h3 res=028 name=nav_controls_toolbar
    x=left y=bottom width=100% height=100%.Navigation controls

:p.Standard navigation controls are provided by clickable buttons for first
page
:artwork runin name='firstpage.bmp'.
:artlink.
:link reftype=hd res=272.
:eartlink.
, last page
:artwork runin name='lastpage.bmp'.
:artlink.
:link reftype=hd res=275.
:eartlink.
, previous page
:artwork runin name='prevpage.bmp'.
:artlink.
:link reftype=hd res=273.
:eartlink.
, and next page
:artwork runin name='nextpage.bmp'.
:artlink.
:link reftype=hd res=274.
:eartlink.
, as well as an entry field to input a specific page number. In addition, the
Up and Down arrow keys may be used to increment or decrement the current page
number.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=007.Navigation pane:elink.
.br
:link reftype=hd res=272.First page:elink.
.br
:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h3 res=030 name=scaling_controls_toolbar
    x=left y=bottom width=100% height=100%.Scaling controls

:p.Scaling of the currently loaded document may be adjusted either by preset
sizes (actual 
:artwork runin name='100perc.bmp'.
:artlink.
:link reftype=hd res=263.
:eartlink., fit in window
:artwork runin name='fitpage.bmp'.
:artlink.
:link reftype=hd res=262.
:eartlink., or fit to window width
:artwork runin name='fitwidth.bmp'.
:artlink.
:link reftype=hd res=264.
:eartlink.) or selected from the dropdown list as either a preset or a
percentage scaling factor.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=260.View menu:elink.
.br
:link reftype=hd res=034.Zoom:elink.
.br
:link reftype=hd res=263.Actual size:elink.
.br
:link reftype=hd res=264.Fit width:elink.
.br
:link reftype=hd res=268.Zoom in:elink.
.br
:link reftype=hd res=269.Zoom out:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h3 res=032 name=find_buttons
    x=left y=bottom width=100% height=100%.Find buttons

:p.Searching for text within supported documents may be accomplished using the
Find... button
:artwork runin name='find.bmp'.
:artlink.
:link reftype=hd res=108.
:eartlink. which in turn opens the
:link reftype=hd res=108.Find dialog:elink.
and the Find again button
:artwork runin name='findagain.bmp'.
:artlink.
:link reftype=hd res=248.
:eartlink.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=240.Edit menu:elink.
.br
:link reftype=hd res=211.Document Context menu:elink.
.br
:link reftype=hd res=246.Find...:elink.
.br
:link reftype=hd res=108.Find dialog:elink.
:edl.


.* ............................................................................
:h3 res=034 name=zoom_tool
    x=left y=bottom width=100% height=100%.Zoom tool

:p.Zooming within the document window is easily accomplished by clicking the 
Zoom tool :artwork runin name='mglass.bmp'. . Once clicked, the state of the
tool is indicated by the button, and the mouse pointer becomes a magnifying
glass :artwork runin name='zoom_in.bmp'.

:p.To use the tool, simply left-click to zoom in and right-click to zoom out.
The current zoom level is shown in the Scaling dropdown on the Toolbar.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=260.View menu:elink.
:edl.


.* ............................................................................
:h2 res=100 name=dialogs
    x=left y=bottom width=100% height=100%.Dialogs, &amp. Listboxes

:p.Further operations are performed via dialogs and listboxes, which help
guide the user through each process and provide further options for the
selected task. Context-sensitive help is available from the :hp2.Help:ehp2.
button or by pressing F1.

:p.:ul compact.
:li.:link reftype=hd res=102.Open File dialog:elink.
:li.:link reftype=hd res=104.Print dialog:elink.
:li.:link reftype=hd res=106.Plugins list:elink.
:li.:link reftype=hd res=108.Find dialog:elink.
:li.:link reftype=hd res=110.Settings dialog:elink.
:li.:link reftype=hd res=112.Go to page dialog:elink.
:li.:link reftype=hd res=114.Document info box:elink.
:li.:link reftype=hd res=116.Fonts info box:elink.
:eul.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=020.Toolbar:elink.
.br
:link reftype=hd res=100.Menus:elink.
:edl.

.* ............................................................................
:h3 res=102 name=open_file_dialog
    x=left y=bottom width=100% height=100%.Open File dialog

:p.The :hp2.Open File dialog:ehp2. provides a selection of available files as
well as a thumbnail sub-panel of the currently-selected file. The list of files
may be narrowed to only supported file types or all files in the selected
directory.

:p.In addition to navigating by drive and directory, a filename dialog is
available at the top, which allows for manual input of the desired filename.

:p.If a thumbnail is available for the document (see discussion of thumbnails
:link reftype=hd res=512.here:elink. and :link reftype=hd res=110.here:elink.),
it will be displayed in the Preview pane on the right side of the Open File
dialog.

:p.The current setting for the Make thumbnails option is reflected by the state
of the :hp2.Make thumbnail checkbox:ehp2.. Using the checkbox, it is possible to
override the configuration for the selected file.

:nt.The :hp2.Make thumbnail checkbox:ehp2. does not change the setting of the
Make thumbnails option. Thus, checking or unchecking this box only affects the
currently selected file. To change the default setting, see the :link 
reftype=hd res=110.Settings dialog:elink..:ent.

:p.:hp2.Help:ehp2. provides context-sensitive information.

:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=022.Open document button:elink.
.br
:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=218.Recent files:elink.
.br
:link reftype=hd res=217.Last link origin:elink.
.br
:link reftype=hd res=219.Save...:elink.
.br
:link reftype=hd res=220.Save as...:elink.
.br
:link reftype=hd res=222.Close:elink.
.br
:link reftype=hd res=512.Thumbnail creation:elink.
.br
:link reftype=hd res=110.Settings dialog:elink.
.br
:link reftype=hd res=104.Print dialog:elink.
:edl.

.* ............................................................................
:h3 res=104 name=print_dialog
    x=left y=bottom width=100% height=100%.Print dialog

:p.The print dialog is divided into five areas, with Print and Cancel buttons
at the bottom.

:p.:hp2.Printer:ehp2.

:p.This area provides a dropdown to select the target printer with the
associated driver listed below, and a Job properties button, which opens the
system printer job settings notebook.

:p.:hp2.Print range and copies:ehp2.

:p.The desired print range (all, current page, range of pages, and even/odd or
both) may be set here, as well as the number of copies and a reverse ordering
option.

:p.:hp2.Print type:ehp2.

:p.Lucide's native output is PostScript. In addition, it is possible to print
as an image (this is the only mode available for non-PostScript printers), and
if desired, the image quality may be set higher for better detail.

:p.There is also a checkbox to select a print to file option (available only
for PostScript printers, as this outputs raw PostScript data to the file).
Selecting this option and clicking Print will bring up the system File Open
container to allow entry of the filename (the .ps extension should be
pre-filled).

:nt.Selecting the option for higher image quality may take considerably
longer to generate output and consume greater system and printer memory in the
process.:ent.

:p.:hp2.Page orientation:ehp2.

:p.Select portrait or landscape orientation for the printed output. 

:nt. If setting orientation in the Job properties for the printer object
itself, it is generally advisable to leave this setting at the default.:ent.

:p.:hp2.Margins (mm):ehp2.

:p.Use the spin buttons or manually enter measurements in millimeters for
margins around the page. The checkbox to ignore printer margins will apply the
measurements to the overall page dimensions, whereas leaving this box
unchecked will result in adding the selected values to the printer's configured
margins.

:p.The selected form is displayed at the bottom of this area.

:p.When all options have been set, click :hp2.Print:ehp2. to send data to the
printer (or to file, if Print to file has been selected), or click
:hp2.Cancel:ehp2. to dismiss the Print dialog and return to the previous view
of the file. :hp2.Help:ehp2. provides context-sensitive information.

:p.The print dialog won't open if Lucide doesn't find any printer. An error
dialog will be shown.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=024.Print button:elink.
.br
:link reftype=hd res=224.Print...:elink.
.br
:link reftype=hd res=514.Controlling print output:elink.
:edl.


.* ............................................................................
:h3 res=106 name=plugins_box
    x=left y=bottom width=100% height=100%.Plugins list

:p.The Plugins list provides a tabular view of each loaded plugin, a brief
description, and a list of supported filename extensions handled. The list is
read-only.

:nt.If a plugin is not listed here, it is either not installed or
:hp2.Lucide:ehp2. was unable to load it.:ent. :hp2.Help:ehp2. provides context-
sensitive information.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=226.Plugins list...:elink.
.br
:link reftype=hd res=114.Document info box:elink.
.br
:link reftype=hd res=116.Fonts info box:elink.
.br
:link reftype=hd res=830.Included plugins:elink.
:edl.


.* ............................................................................
:h3 res=108 name=find_dialog
    x=left y=bottom width=100% height=100%.Find dialog

:p.If the document contains text, the content may be searched using the Find
dialog. Enter the string to locate, and select the appropriate options for case
matching and/or searching backwards through the document, and click
:hp2.OK:ehp2. to begin the search or :hp2.Cancel:ehp2. to close the dialog
without searching. :hp2.Help:ehp2. provides context-sensitive information.

:p.During the search, a progress panel is displayed, and if no results are
found, a message is presented.

:p.Matching words in the document will be highlighted.

:nt.It is currently not possible to search image PDFs or other files which
do not contain actual text which may be selected. To determine the type of
document being viewed, try selecting some text with the left mouse button. If
the text is selectable, then searching should function as expected.

:p.The maximum length of the search string is 100 characters. Attempting to
paste a longer string into the search dialog box will result in none of the
data being pasted.:ent.

:p.:hp2.Help:ehp2. provides context-sensitive information.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=246.Find...:elink.
.br
:link reftype=hd res=248.Find again:elink.
.br
:link reftype=hd res=032.Find buttons:elink.
.br
:link reftype=hd res=242.Copy:elink.
.br
:link reftype=hd res=244.Select all:elink.
:edl.


.* ............................................................................
:h3 res=110 name=settings_dialog
    x=left y=bottom width=100% height=100%.Settings dialog

:p.The Settings dialog allows the configuration of cross-document defaults for
page layout, zoom level (scaling), and thumbnail creation. These defaults may
be overridden on a per-session-window basis in the case of page layout and
zoom level. Thus, once the defaults have been changed for the currently-loaded
document, subsequent documents opened in the same :hp2.Lucide:ehp2. window will
receive the overridden settings. Documents opened in new windows, however, will
revert to the defaults set here.

:p.Clicking :hp2.OK:ehp2. saves any changes made, while :hp2.Cancel:ehp2. keeps
any previous settings intact. :hp2.Help:ehp2. provides context-sensitive
information.

:p.:hp2.More about thumbnails:ehp2.

:p.Thumbnail creation may be overridden on a per-file basis at the time of
opening a new file by selecting or de-selecting the Make thumbnail checkbox in
the :link reftype=hd res=102.Open File dialog:elink..

:p.In order for the thumbnail to be saved to disk, the file must have been
opened from writable media, the user must have rights to modify files on the
volume, and the filesystem must support extended attributes.

:note text='Note 1'.As a security precaution, thumbnails are :hp3.never:ehp3.
created for encrypted PDFs.

:note text='Note 2'.Thumbnails are stored in extended attributes, attached to
the original file. Creating a thumbnail does not alter the content of the
original file in any way, though subsequently copying a file with a thumbnail
to a volume which does not support extended attributes will cause the thumbnail
to not be copied. Likewise, transmitting the file over the internet via FTP or
attaching it to an email (if not zipped or contained within some other archive)
will result in the thumbnail not being sent with the file. The original file
(and generated thumbnail, if created) will remain unaltered.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=284.Single page layout:elink.
.br
:link reftype=hd res=285.Continuous layout:elink.
.br
:link reftype=hd res=030.Scaling controls:elink.
.br
:link reftype=hd res=512.Thumbnail creation:elink.
:edl.


.* ............................................................................
:h3 res=112 name=go_to_page_dialog
    x=left y=bottom width=100% height=100%.Go to page dialog

:p.The Go to page dialog allows the input of the desired page number for quick
navigation. Enter the page number in the box and click :hp2.OK:ehp2. to begin
the search or :hp2.Cancel:ehp2. :hp2.Help:ehp2. provides context-sensitive
information.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=272.First page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=028.Navigation controls:elink.
:edl.


.* ............................................................................
:h3 res=114 name=document_info_box
    x=left y=bottom width=100% height=100%.Document info box 

:p.The Document info box provides a scrollable list of details describing the
current file. The type of information displayed depends upon the type of file
as well as what was used to create it (not all creators provide all details).

:p.While the content is read-only, it is possible to select one or more lines
with the mouse using standard OS/2 modifiers, such as :hp2.Ctrl+/:ehp2. to
select all, :hp2.Ctrl+LMB:ehp2. to select non-contiguous lines, or
:hp2.Shift+LMB:ehp2. to select a range, and then copy the content of the
selected lines to the clipboard either using :hp2.Ctrl+Ins:ehp2. or
:hp2.Ctrl+C:ehp2..

:p.:hp2.Close:ehp2. dismisses the box, and :hp2.Help:ehp2. provides context-
sensitive information.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=106.Plugins list:elink.
.br
:link reftype=hd res=226.Plugins list...:elink.
.br
:link reftype=hd res=116.Fonts info box:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=800.Approach:elink.
:edl.


.* ............................................................................
:h3 res=116 name=fonts_info_box
    x=left y=bottom width=100% height=100%.Fonts info box 

:p.The Fonts info box provides a tabular view of each font used in the
document, it's type, whether it has been embedded in the document or not, and
if substituted, what font is being used in its place.

:p.While the content is read-only, it is possible to select one or more lines
with the mouse using standard OS/2 modifiers, such as :hp2.Ctrl+/:ehp2. to
select all, :hp2.Ctrl+LMB:ehp2. to select non-contiguous lines, or
:hp2.Shift+LMB:ehp2. to select a range, and then copy the content of the
selected lines to the clipboard either using :hp2.Ctrl+Ins:ehp2. or
:hp2.Ctrl+C:ehp2..

:p.:hp2.Close:ehp2. dismisses the box, and :hp2.Help:ehp2. provides context-
sensitive information.



:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=106.Plugins list:elink.
.br
:link reftype=hd res=226.Plugins list...:elink.
.br
:link reftype=hd res=114.Document info box:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=800.Approach:elink.
:edl.


.* ............................................................................
:h3 res=118 name=password_dialog
    x=left y=bottom width=100% height=100%.Password dialog

:p.If the document you wish to open is encrypted, you will be presented with
the Password dialog. Enter the password in the box and click :hp2.OK:ehp2. to
decrypt or :hp2.Cancel:ehp2. to abort. :hp2.Help:ehp2. provides context-
sensitive information.

:p.Reasons for decryption failure include:

:note text='Incorrect password'.In this case, :hp2.Lucide:ehp2. will present
the Password dialog continuously, until the correct password is entered or
until the :hp2.Cancel:ehp2. button or Esc is pressed. Once returned to an empty
Document pane, you may select another file to open.

:note text='Unsupported encryption type'.:hp2.Lucide:ehp2. makes no distinction
between password protected documents or other security methods which it cannot
currently decrypt. Accordingly, you may be presented with the Password dialog
for a document encrypted using a certificate, where no password will be
accepted. :hp2.Lucide:ehp2. has no way of opening such files.

:note text='Canceling'.Clicking the :hp2.Cancel:ehp2. button or Esc will dismiss
the Password dialog and return to an empty Document pane.

:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=102.Open File dialog:elink.
.br
:link reftype=hd res=730.PDF security:elink.
.br
:link reftype=hd res=840.Security:elink.
:edl.


.* ............................................................................
:h3 res=120 name=progress_dialog
    x=left y=bottom width=100% height=100%.Progress dialog

:p.The Progress dialog is presented whenever an operation takes several moments
to complete. In some cases, you may be presented with a selectable
:hp2.Cancel:ehp2. button to abort the operation.


.* ............................................................................
:h2 res=200 name=menu
    x=left y=bottom width=100% height=100%.Menu

:p.The main menu provides the following functions and sub-menus&colon.


:p.:ul compact.
:li.:link reftype=hd res=210.Document menu:elink.
:li.:link reftype=hd res=211.Document Context menu:elink.
:li.:link reftype=hd res=240.Edit menu:elink.
:li.:link reftype=hd res=260.View menu:elink.
:li.:link reftype=hd res=300.Window menu:elink.
:li.:link reftype=hd res=360.Help menu:elink.
:eul.
:p.


.* ............................................................................
:h3 res=210 name=document_menu
    x=left y=bottom width=100% height=100%.Document menu

:p.The Document menu provides the following selections:

:p.:ul compact.
:li.:link reftype=hd res=212.New window:elink.
:li.:link reftype=hd res=214.Open...:elink.
:li.:link reftype=hd res=216.Next/Previous:elink.
:li.:link reftype=hd res=218.Recent files:elink.
:li.:link reftype=hd res=217.Last link origin:elink.
:li.:link reftype=hd res=219.Save...:elink.
:li.:link reftype=hd res=220.Save as...:elink.
:li.:link reftype=hd res=222.Close:elink.
:li.:link reftype=hd res=224.Print...:elink.
:li.:link reftype=hd res=226.Plugins list...:elink.
:li.:link reftype=hd res=228.Exit:elink.
:eul.
:p.

.* ............................................................................
:h4 res=212 name=new_window
    x=left y=bottom width=100% height=100%.New window

:p.This creates a new :hp2.Lucide:ehp2. window configured similarly to the
current window. Multiple windows operate independently of one another, making
it possible to open different files (or types of files) from different
locations, and to scale each differently.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=218.Recent files:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.


.* ............................................................................
:h4 res=214 name=open
    x=left y=bottom width=100% height=100%.Open...

:p.This opens the :link reftype=hd res=102.Open File dialog:elink. in the
current window and subsequently loads the selected file using the current view
configuration.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=212.New window:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=218.Recent files:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.


.* ............................................................................
:h4 res=216 name=next_previous
    x=left y=bottom width=100% height=100%.Next/Previous

:p.This opens the next or previous supported file type in the current
directory, replacing the file being viewed.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=212.New window:elink.
.br
:link reftype=hd res=218.Recent files:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.


.* ............................................................................
:h4 res=218 name=recent_files
    x=left y=bottom width=100% height=100%.Recent files

:p.The Recent files list allows for quick selection from the nine
most-recently-opened files. It also provides a Clear option to empty the list.

:p.The file selected will replace the file currently being viewed.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=212.New window:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.

.* ............................................................................
:h4 res=217 name=Last_link_origin
    x=left y=bottom width=100% height=100%.Last link origin

:p.This menu selection is only enabled if you have selected an internal
link. If selected it will return you to the point in the document where
the link originated.

:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
:edl.

.* ............................................................................
:h4 res=219 name=save
    x=left y=bottom width=100% height=100%.Save...

:p.This menu selection saves the current file. This is only available
for PDF fill in forms. If the original (blank) form should be preserved use 
:link reftype=hd res=220.Save as...:elink.. 
:p.Save actually saves to a temporary file which it loads then saves 
to the original file which is then reloaded. It then deletes the temporary file. 
:p.You may see signs of the reloads on the screen. If a save fails the 
temporary file may remain in your %TEMP% directory. This is a Poppler 
limitation as it only allows for save as to a different file name.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=218.Recent files:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.

.* ............................................................................
:h4 res=220 name=save_as
    x=left y=bottom width=100% height=100%.Save as...

:p.This menu selection opens the standard system file selection dialog to allow
for the saving of the current file to a different filename. This is often used
when filling in PDF forms, where the original should be preserved.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=219.Save...:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=218.Recent files:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.


.* ............................................................................
:h4 res=222 name=close
    x=left y=bottom width=100% height=100%.Close

:p.This closes the current file, leaving the window in its current
configuration. From this state, a new file may be opened through the usual
methods.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=212.New window:elink.
.br
:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=218.Recent files:elink.
:edl.


.* ............................................................................
:h4 res=224 name=print
    x=left y=bottom width=100% height=100%.Print...

:p.This opens the :link reftype=hd res=104.Print dialog:elink. where job
options may be set before sending the file to the selected printer.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=104.Print dialog:elink.
:edl.

.* ............................................................................
:h4 res=226 name=plugins_list
    x=left y=bottom width=100% height=100%.Plugins list...

:p.The Plugins list... Document menu option opens the :link reftype=hd res=106.
Plugins list:elink., which provides a tabular view of each loaded plugin, a
brief description, and a list of supported filename extensions handled. The
list is read-only.

:nt.If a plugin is not listed here, it is either not installed or
:hp2.Lucide:ehp2. was unable to load it.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=106.Plugins list:elink.
.br
:link reftype=hd res=116.Fonts info box:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=830.Included plugins:elink.
:edl.


.* ............................................................................
:h4 res=228 name=exit
    x=left y=bottom width=100% height=100%.exit

:p.This exits the current :hp2.Lucide:ehp2. window completely, leaving any
other instances running.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=212.New window:elink.
.br
:link reftype=hd res=214.Open...:elink.
.br
:link reftype=hd res=216.Next/Previous:elink.
.br
:link reftype=hd res=218.Recent files:elink.
.br
:link reftype=hd res=222.Close:elink.
:edl.

.* ............................................................................
:h3 res=211 name=document_context_menu
    x=left y=bottom width=100% height=100%.Document context menu

:p.Right click in the document pane to open this menu.
:p.The Document context menu provides the following selections:

:p.:ul compact.
:li.:link reftype=hd res=217.Last link origin:elink.
:li.:link reftype=hd res=242.Copy:elink.
:li.:link reftype=hd res=244.Select all:elink.
:li.:link reftype=hd res=246.Find...:elink.
:li.:link reftype=hd res=248.Find again:elink.
:li.:link reftype=hd res=224.Print...:elink.
:eul.
:p.

.* ............................................................................
:h3 res=240 name=edit_menu
    x=left y=bottom width=100% height=100%.Edit menu

:p.The Edit menu provides the following selections:

:p.:ul compact.
:li.:link reftype=hd res=242.Copy:elink.
:li.:link reftype=hd res=244.Select all:elink.
:li.:link reftype=hd res=246.Find...:elink.
:li.:link reftype=hd res=248.Find again:elink.
:li.:link reftype=hd res=250.Settings:elink.
:li.:link reftype=hd res=228.Exit:elink.
:eul.
:p.


.* ............................................................................
:h4 res=242 name=copy
    x=left y=bottom width=100% height=100%.Copy

:p.This copies the current selection to the system clipboard, subject to size
limitations of the clipboard itself.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=420.Mouse buttons and gestures:elink.
.br
:link reftype=hd res=502.Selecting content:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h4 res=244 name=select_all
    x=left y=bottom width=100% height=100%.Select all

:p.This selects all of the current view of the document.

:nt.It may not be possible to copy all of the selected content to the system
clipboard due to size limitations of the clipboard itself.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=242.Copy:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=420.Mouse buttons and gestures:elink.
.br
:link reftype=hd res=502.Selecting content:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h4 res=246 name=find
    x=left y=bottom width=100% height=100%.Find

:p.This opens the :link reftype=hd res=108.Find dialog:elink. which presents
the user with an input box to enter the search criteria.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=032.Find tool:elink.
.br
:link reftype=hd res=108.Find dialog:elink.
.br
:link reftype=hd res=504.Searching for text:elink.
.br
:link reftype=hd res=242.Copy:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=502.Selecting content:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h4 res=248 name=find_again
    x=left y=bottom width=100% height=100%.Find again

:p.This repeats the search using the current search criteria, stopping at the
next highlighted block of found text.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=032.Find tool:elink.
.br
:link reftype=hd res=108.Find dialog:elink.
.br
:link reftype=hd res=504.Searching for text:elink.
.br
:link reftype=hd res=242.Copy:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=502.Selecting content:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h4 res=250 name=settings
    x=left y=bottom width=100% height=100%.Settings

:p.This opens the :link reftype=hd res=110.Settings dialog:elink., which allows
the configuration of cross-document defaults for Page layout and Zoom level
(scaling).

:nt.Defaults may be overridden on a per-session-window basis. Thus, once the
defaults have been changed for the currently-loaded document, subsequent
documents opened in the same :hp2.Lucide:ehp2. window will receive the
overridden settings. Documents opened in new windows, however, will revert to
the defaults set in the dialog.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=284.Single page layout:elink.
.br
:link reftype=hd res=285.Continuous layout:elink.
.br
:link reftype=hd res=030.Scaling controls:elink.
:edl.


.* ............................................................................
:h3 res=260 name=view_menu
    x=left y=bottom width=100% height=100%.View menu

:p.The View menu provides the following selections:

:p.:ul compact.
:li.:link reftype=hd res=262.Fit in window:elink.
:li.:link reftype=hd res=263.Actual size:elink.
:li.:link reftype=hd res=264.Fit width:elink.
:li.:link reftype=hd res=268.Zoom in:elink.
:li.:link reftype=hd res=269.Zoom out:elink.
:li.:link reftype=hd res=272.First page:elink.
:li.:link reftype=hd res=273.Previous page:elink.
:li.:link reftype=hd res=274.Next page:elink.
:li.:link reftype=hd res=275.Last page:elink.
:li.:link reftype=hd res=276.Go to page...:elink.
:li.:link reftype=hd res=280.Rotate 90&deg. CW:elink.
:li.:link reftype=hd res=281.Rotate 90&deg. CCW:elink.
:li.:link reftype=hd res=284.Single page:elink.
:li.:link reftype=hd res=285.Continuous:elink.
:li.:link reftype=hd res=290.Document info...:elink.
:li.:link reftype=hd res=291.Fonts info...:elink.
:eul.
:p.


.* ............................................................................
:h4 res=262 name=fit_in_window
    x=left y=bottom width=100% height=100%.Fit in window

:p.This sets the current :link reftype=hd res=034.Zoom level:elink. (scaling)
such that a single page (regardless the setting for :link reftype=hd
res=284.Single page:elink. vs :link reftype=hd res=285.Continuous:elink.
layout) fits within the boundaries of the :link reftype=hd res=008.Document
pane:elink.. Resizing the Document pane via the mouse, standard window
controls, or options on the :link reftype=hd res=300.Window menu:elink. will
cause the view to scale proportionally.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=030.Scaling controls:elink.
.br
:link reftype=hd res=034.Zoom:elink.
.br
:link reftype=hd res=263.Actual size:elink.
.br
:link reftype=hd res=264.Fit width:elink.
.br
:link reftype=hd res=268.Zoom in:elink.
.br
:link reftype=hd res=269.Zoom out:elink.
.br
:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=263 name=actual_size
    x=left y=bottom width=100% height=100%.Actual size

:p.This sets the current :link reftype=hd res=034.Zoom level:elink. (scaling)
such that a single page (regardless the setting for :link reftype=hd
res=284.Single page:elink. vs :link reftype=hd res=285.Continuous:elink.
layout) is displayed at its original scale in the :link reftype=hd
res=008.Document pane:elink.. Resizing the Document pane via the mouse,
standard window controls, or options on the :link reftype=hd res=300.Window
menu:elink. will increase or decrease the area surrounding the currently viewed
page (the relative size of the page will remain unchanged).

:nt.When in :link reftype=hd res=304.Presentation mode:elink., scaling will
return to a level necessary to present a single page in the current screen
resolution.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=030.Scaling controls:elink.
.br
:link reftype=hd res=034.Zoom:elink.
.br
:link reftype=hd res=262.Fit in window:elink.
.br
:link reftype=hd res=264.Fit width:elink.
.br
:link reftype=hd res=268.Zoom in:elink.
.br
:link reftype=hd res=269.Zoom out:elink.
.br
:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=264 name=fit_width
    x=left y=bottom width=100% height=100%.Fit width

:p.This sets the current :link reftype=hd res=034.Zoom level:elink. (scaling)
such that a single page (regardless the setting for :link reftype=hd
res=284.Single page:elink. vs :link reftype=hd res=285.Continuous:elink.
layout) fits within the boundaries of the width of the :link reftype=hd
res=008.Document pane:elink.. A vertical scrollbar may be presented if the
length of the current view exceeds the available vertical space in the Document
pane. Resizing the Document pane via the mouse, standard window controls, or
options on the :link reftype=hd res=300.Window menu:elink. will cause the view
to scale proportionally.

:nt.When in :link reftype=hd res=304.Presentation mode:elink., scaling will
return to a level necessary to present a single page in the current screen
resolution.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=030.Scaling controls:elink.
.br
:link reftype=hd res=034.Zoom:elink.
.br
:link reftype=hd res=263.Actual size:elink.
.br
:link reftype=hd res=262.Fit in window:elink.
.br
:link reftype=hd res=268.Zoom in:elink.
.br
:link reftype=hd res=269.Zoom out:elink.
.br
:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=268 name=zoom_in
    x=left y=bottom width=100% height=100%.Zoom in

:p.Zooming in from the menu causes the current view in the :link reftype=hd
res=008.Document pane:elink. to increase to the next preset :link reftype=hd
res=034.Zoom level:elink. (scaling) such that a single page (regardless the
setting for :link reftype=hd res=284.Single page:elink. vs :link reftype=hd
res=285.Continuous:elink. layout) fits within the boundaries of the :link
reftype=hd res=008.Document pane:elink.. Resizing the Document pane via the
mouse, standard window controls, or options on the :link reftype=hd
res=300.Window menu:elink. will increase or decrease the area surrounding the
currently viewed page (the relative size of the page will remain unchanged).
Horizontal and/or vertical scrollbars may be presented if the current zoom
level exceeds the size of the Document pane.

:nt.When in :link reftype=hd res=304.Presentation mode:elink., scaling will
return to a level necessary to present a single page in the current screen
resolution. It is possible to zoom in and out using the :link reftype=hd
res=400.Ctrl++/Ctrl+- Keyboard accelerators:elink. (the selected zoom level
will not be displayed).:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=030.Scaling controls:elink.
.br
:link reftype=hd res=034.Zoom:elink.
.br
:link reftype=hd res=263.Actual size:elink.
.br
:link reftype=hd res=264.Fit width:elink.
.br
:link reftype=hd res=269.Zoom out:elink.
.br
:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=269 name=zoom_out
    x=left y=bottom width=100% height=100%.Zoom out

:p.Zooming out from the menu causes the current view in the :link reftype=hd
res=008.Document pane:elink. to decrease to the next preset :link reftype=hd
res=034.Zoom level:elink. (scaling) such that as many pages (regardless the
setting for :link reftype=hd res=284.Single page:elink. vs :link reftype=hd
res=285.Continuous:elink. layout) as will fit within the boundaries of the
:link reftype=hd res=008.Document pane:elink. are displayed vertically.
Resizing the Document pane via the mouse, standard window controls, or options
on the :link reftype=hd res=300.Window menu:elink. will increase or decrease
the area surrounding the currently viewed page(s), and more or fewer pages will
be displayed (the relative size of the page will remain unchanged).

:nt.When in :link reftype=hd res=304.Presentation mode:elink., scaling will
return to a level necessary to present a single page in the current screen
resolution.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=030.Scaling controls:elink.
.br
:link reftype=hd res=034.Zoom:elink.
.br
:link reftype=hd res=263.Actual size:elink.
.br
:link reftype=hd res=264.Fit width:elink.
.br
:link reftype=hd res=268.Zoom in:elink.
.br
:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=272 name=first_page
    x=left y=bottom width=100% height=100%.First page

:p.This navigates the current view to the beginning of the document.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=273 name=previous_page
    x=left y=bottom width=100% height=100%.Previous page

:p.This navigates the current view to the preceding page of the document.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=272.First page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=274 name=next_page
    x=left y=bottom width=100% height=100%.Next page

:p.This navigates the current view to the succeeding page of the document.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=272.First page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=275 name=last_page
    x=left y=bottom width=100% height=100%.Last page

:p.This navigates the current view to the final page of the document.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=272.First page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=276 name=go_to_page
    x=left y=bottom width=100% height=100%.Go to page...

:p.This opens the :link reftype=hd res=112.Go to page dialog:elink. which
allows for quick navigation to a desired page.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=028.Navigation controls:elink.
.br
:link reftype=hd res=007.Navigation pane:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=280 name=rotate_cw
    x=left y=bottom width=100% height=100%.Rotate 90&deg. CW

:p.This turns the current view sideways to the right.

:nt.When in :link reftype=hd res=304.Presentation mode:elink., scaling will
return to a level necessary to present a single page in the current screen
resolution, preserving the desired rotation.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=281.Rotate 90&deg. CCW:elink.
.br
:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=281 name=rotate_ccw
    x=left y=bottom width=100% height=100%.Rotate 90&deg. CCW

:p.This turns the current view sideways to the left.

:nt.When in :link reftype=hd res=304.Presentation mode:elink., scaling will
return to a level necessary to present a single page in the current screen
resolution, preserving the desired rotation.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=280.Rotate 90&deg. CW:elink.
.br
:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=284 name=single_page
    x=left y=bottom width=100% height=100%.Single page

:p.This displays the selected document one page at a time, at the proportions
specified within the document itself. The vertical scrollbar will reference
only a single page at a time, requiring either keyboard, menu, or Navigation
panel interaction to scroll through the document.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=285.Continuous:elink.
.br
:link reftype=hd res=272.First page:elink.
.br
:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=420.Mouse buttons and gestures:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=285 name=continuous
    x=left y=bottom width=100% height=100%.Continuous

:p.This displays the selected document in multi-page format, with pages
delineated but with the ability to smoothly scroll across page boundaries. The
vertical scrollbar will reference the current position within the entire
file, allowing mouse, keyboard, menu, or the Navigation panel to move through
the document.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=284.Single page:elink.
.br
:link reftype=hd res=272.First page:elink.
.br
:link reftype=hd res=273.Previous page:elink.
.br
:link reftype=hd res=274.Next page:elink.
.br
:link reftype=hd res=275.Last page:elink.
.br
:link reftype=hd res=276.Go to page...:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=420.Mouse buttons and gestures:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=290 name=document_info
    x=left y=bottom width=100% height=100%.Document info...

:p.This opens the :link reftype=hd res=114.Document info box:elink. which
provides details about the currently opened file.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=106.Plugins list:elink.
.br
:link reftype=hd res=226.Plugins list...:elink.
.br
:link reftype=hd res=291.Fonts info...:elink.
.br
:link reftype=hd res=116.Fonts info box:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=800.Approach:elink.
:edl.


.* ............................................................................
:h4 res=291 name=fonts_info
    x=left y=bottom width=100% height=100%.Fonts info...

:p.This displays the :link reftype=hd res=116.Fonts info box:elink. which
provides details about fonts used (and substituted) in the currently opened
file.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=106.Plugins list:elink.
.br
:link reftype=hd res=226.Plugins list...:elink.
.br
:link reftype=hd res=290.Document info...:elink.
.br
:link reftype=hd res=114.Document info:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=800.Approach:elink.
:edl.


.* ............................................................................
:h3 res=300 name=window_menu
    x=left y=bottom width=100% height=100%.Window menu

:p.The Window menu provides the following selections:

:p.:ul compact.
:li.:link reftype=hd res=302.Show navigation pane:elink.
:li.:link reftype=hd res=303.Full screen:elink.
:li.:link reftype=hd res=304.Presentation:elink.
:eul.
:p.


.* ............................................................................
:h4 res=302 name=show_nav_pane
    x=left y=bottom width=100% height=100%.Show navigation pane

:p.Like the :link reftype=hd res=026.Show/hide navigation pane:elink.
toolbar button and the :link reftype=hd res=400.F9 Keyboard accelerator:elink.,
this menu option toggles the display of the :link reftype=hd res=007.Navigation
pane:elink..


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=007.Navigation pane:elink.
.br
:link reftype=hd res=026.Show/hide navigation pane:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=028.Navigation controls:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:p.
:edl.


.* ............................................................................
:h4 res=303 name=full_screen
    x=left y=bottom width=100% height=100%.Full screen

:p.This toggles the display to fill the screen, removing window borders and
decorations. The menu is moved flush to the top of the screen. The toolbar
remains in place, and if enabled, the :link reftype=hd res=007.Navigation
pane:elink. remains visible. All :link reftype=hd res=400.Keyboard
accelerators:elink. are functional, as well. This view mode may also be
selected via the :link reftype=hd res=400.F11 Keyboard accelerator:elink..

:nt.It is possible to surface other windows in front of :hp2.Lucide:ehp2. in
this mode.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=304.Presentation:elink.
.br
:link reftype=hd res=026.Show/hide navigation pane:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=028.Navigation controls:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h4 res=304 name=presentation
    x=left y=bottom width=100% height=100%.Presentation

:p.This toggles the display to fill the screen, removing window borders and
decorations, the :link reftype=hd res=007.Navigation pane:elink. (if
previously enabled, scrollbars, and the menu. Some :link reftype=hd
res=400.Keyboard accelerators:elink. are disabled. This view
mode may also be selected via the :link reftype=hd res=400.F5 Keyboard
accelerator:elink..

:p.Remote control of :hp2.Lucide:ehp2. (most often used in this mode) may be
accomplished using the PIPE interface discussed in the section :link reftype=hd
res=440. Remote control functions:elink..

:note text='Note 1'.It is possible to surface other windows in front of
:hp2.Lucide:ehp2. in this mode.

:note text='Note 2'.When in Presentation mode, scaling will return to a level
necessary to present a single page in the current screen resolution. It is
possible to zoom in and out using the :link reftype=hd res=400.Ctrl++/Ctrl+-
Keyboard accelerators:elink. (the selected zoom level will not be displayed).


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=303.Full screen:elink.
.br
:link reftype=hd res=026.Show/hide navigation pane:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=028.Navigation controls:elink.
.br
:link reftype=hd res=440.Remote control functions:elink.
:edl.


.* ............................................................................
:h3 res=360 name=help_menu
    x=left y=bottom width=100% height=100%.Help menu

:p.The Help menu provides&colon.

:parml compact tsize=10 break=none.
:pt.:hp2.Contents...:ehp2.
:pd.This user guide, from the beginning
:pt.:hp2.Keys help...:ehp2.
:pd.Assistance with keyboard accelerators
:pt.:hp2.PDF files help...:ehp2.
:pd.Information about the PDF format and how :hp2.Lucide:ehp2. renders different types of PDFs
:pt.:hp2.Image files help...:ehp2.
:pd.Information about various image formats handled by Lucide
:pt.:hp2.Product information:ehp2.
:pd.About :hp2.Lucide:ehp2.
:eparml.


.* ............................................................................
:h2 res=400 name=keyboard_accelerators
    x=left y=bottom width=100% height=100%.Keyboard accelerators

:p.In addition to the standard system keyboard commands for window controls
(e.g., Alt+F4 to exit, Alt+F5 to restore, Alt+F7 to move, Alt+F8 to resize,
Alt+F9 to minimize, etc.), program-specific keyboard accelerators (hotkeys)
provide quick access to many of :hp2.Lucide's:ehp2. functions&colon.

:hp2.
:table cols='15 48'.
:row.
:c.HOTKEY
:c.ACTION
:row.
:c.Ctrl+O
:c.opens the :link reftype=hd res=102.Open File dialog:elink.
:row.
:c.Up
:c.when focus is in the :link reftype=hd res=008.Document pane:elink. or the
:link reftype=hd res=007.Navigation pane:elink., scroll up; when focus is in
the :link reftype=hd res=028.Toolbar page number entry field:elink. or the
:link reftype=hd res=112.Go to page dialog:elink., increment page number
:row.
:c.Dn
:c.when focus is in the :link reftype=hd res=008.Document pane:elink. or the
:link reftype=hd res=007.Navigation pane:elink., scroll down; when focus is in
the :link reftype=hd res=028.Toolbar page number entry field:elink. or the
:link reftype=hd res=112.Go to page dialog:elink., decrement page number
:row.
:c.Ctrl+Shift+Home
:c.open the first supported document in the current directory
:row.
:c.Ctrl+Shift+End
:c.open the last supported document in the current directory
:row.
:c.Ctrl+Shift+PgUp
:c.open the previous supported document in the current directory
:row.
:c.Ctrl+Shift+PgDn
:c.open the next supported document in the current directory
:row.
:c.Ctrl+K
:c.save the current document :link reftype=hd res=217.Last link origin:elink.)
:row.
:c.Ctrl+S
:c.save the current document :link reftype=hd res=219.Save...:elink.)
:row.
:c.Ctrl+A
:c.save the current document with a different name (see :link reftype=hd
res=220.Save as...:elink.)
:row.
:c.Ctrl+F
:c.opens the :link reftype=hd res=108.Find dialog:elink.
:row.
:c.Ctrl+I
:c.opens the :link reftype=hd res=114.Document info box:elink.
:row.
:c.Ctrl+N
:c.opens the :link reftype=hd res=112.Go to page dialog:elink.
:row.
:c.Ctrl+P
:c.opens the :link reftype=hd res=104.Print dialog:elink.
:row.
:c.Ctrl+X
:c.exits the current window (see :link reftype=hd res=228.Exit:elink.)
:row.
:c.Ctrl+0
:c.:link reftype=hd res=262.Fit in window:elink.
:row.
:c.Ctrl+1
:c.:link reftype=hd res=263.Actual size:elink.
:row.
:c.Ctrl+2
:c.:link reftype=hd res=264.Fit width:elink.
:row.
:c.+
:c.:link reftype=hd res=274.Next page:elink.
:row.
:c.-
:c.:link reftype=hd res=273.Previous page:elink.
:row.
:c.Ctrl++
:c.:link reftype=hd res=268.Zoom in:elink.
:row.
:c.Ctrl+-
:c.:link reftype=hd res=269.Zoom out:elink.
:row.
:c.Ctrl+Shift++
:c.rotates the current view clockwise 90&deg. (see :link reftype=hd
res=280.Rotate 90&deg. CW:elink.)
:row.
:c.Ctrl+Shift+-
:c.rotates the current view counter-clockwise 90&deg. (see :link reftype=hd
res=281.Rotate 90&deg. CCW:elink.)
:row.
:c.Ctrl+/
:c.selects all content in the current view
:row.
:c.Ctrl+Ins
:c.copies selected content to the system clipboard
:row.
:c.F1
:c.displays help
:row.
:c.F5
:c.toggles :link reftype=hd res=304.Presentation:elink. mode
:row.
:c.F9
:c.toggles the :link reftype=hd res=007.Navigation pane:elink.
:row.
:c.F10
:c.accesses the menu
:row.
:c.F11
:c.toggles :link reftype=hd res=303.Full screen:elink. mode
:row.
:c.Ctrl+F4
:c.closes the current document (see :link reftype=hd res=222.Close:elink.)
:etable.
:ehp2.


.* ............................................................................
:h2 res=420 name=mouse
    x=left y=bottom width=100% height=100%.Mouse buttons and gestures

:p.Mouse buttons and gestures available in :hp2.Lucide:ehp2. provide the
following functions&colon.

:hp2.
:table cols='15 48'.
:row.
:c.GESTURE
:c.ACTION
:row.
:c.LMB
:c.selects a given menu item or form element, or if the Zoom tool
:link reftype=hd res=034.Zoom:elink. has been selected and the pointer has
changed to the magnifying glass, increases the zoom level
:row.
:c.RMB
:c.when the Zoom tool :link reftype=hd res=034.Zoom:elink. has been selected
and the pointer has changed to the magnifying glass, decreases the zoom level
:row.
:c.LMB drag
:c.selects a range of document content, either by dragging along the content
to be selected or by dragging up and down the margin area (or outside it) to
select entire lines or sections.
:row.
:c.RMB drag
:c.when the Zoom tool :link reftype=hd res=034.Zoom:elink. has not
been selected, the pointer changes to the positioning hand and moves the
displayed section within the :link reftype=hd res=008.Document pane:elink..
:etable.
:ehp2.


.* ............................................................................
:h2 res=440 name=remote_control
    x=left y=bottom width=100% height=100%.Remote control functions

:p.The first instance of :hp2.Lucide:ehp2. will create a named pipe
\PIPE\LUCIDE. You may then send following commands to this pipe&colon.

:hp2.
:table cols='15 48'.
:row.
:c.COMMAND
:c.ACTION
:row.
:c.&dollar.prev
:c.switch to the previous page
:row.
:c.&dollar.next
:c.switch to the next page
:row.
:c.&dollar.presentation
:c.switch to presentation mode (even if minimized)
:row.
:c.&dollar.minimize
:c.mimimize Lucide (even if fullscreen)
:row.
:c.&dollar.rotate
:c.rotate 90 degrees clockwise
:row.
:c.&dollar.zoomin
:c.zoom in
:row.
:c.&dollar.zoomout
:c.zoom out
:row.
:c.&dollar.zoomoriginal
:c.zoom to actual size
:etable.
:ehp2.


.* ............................................................................
:h2 res=500 name=howto
    x=left y=bottom width=100% height=100%.How do I...
:hp2.How do I...:ehp2.

:p.:ul compact.
:li.:link reftype=hd res=502....select content?:elink.
:li.:link reftype=hd res=504....search for text?:elink.
:li.:link reftype=hd res=506....fill in PDF forms?:elink.
:li.:link reftype=hd res=508....control Lucide remotely?:elink.
:li.:link reftype=hd res=510....configure Lucide to open hyperlinks?:elink.
:li.:link reftype=hd res=512....disable auto-creation of thumbnails?:elink.
:li.:link reftype=hd res=513....remove a thumbnail from a file?:elink.
:li.:link reftype=hd res=514....direct print output and layout?:elink.
:li.:link reftype=hd res=580....get help with problems?:elink.
:li.:link reftype=hd res=582....make a feature request?:elink.
:li.:link reftype=hd res=584....get involved with the Lucide project?:elink.
:eul.
:p.


.* ............................................................................
:h3 res=502 name=select_content
    x=left y=bottom width=100% height=100%.select content?
:p.:hp2.How do I...:ehp2.
:p.:hp2....select content?:ehp2.

:p.Selecting text in a PDF is accomplished either by dragging the left mouse
button over the text to be selected (or along the margin area), selecting all
text in the current view via Edit | Select all, or using the standard OS/2
keyboard accelerator, :hp2.Ctrl+/:ehp2..

:p.It is not currently possible to select non-text elements on a page.

:nt.Other plugins may allow for selecting different types of elements. Refer
to the documentation for the specific plugin to determine its capabilities and
how to use them.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=242.Copy:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=420.Mouse buttons and gestures:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h3 res=504 name=search_text
    x=left y=bottom width=100% height=100%.search for text?
:p.:hp2.How do I...:ehp2.
:p.:hp2....search for text?:ehp2.

:p.Searching for text in a PDF is accomplished via the :link reftype=hd
res=108.Find dialog:elink., accessed through any of the following methods
&colon.

:p.:ul compact.
:li.:link reftype=hd res=246.Find...:elink.
:li.:link reftype=hd res=108.Find dialog:elink.
:li.:link reftype=hd res=400.Ctrl+F Keyboard accelerator:elink.
:eul.

:nt.Some plugins may not allow for searching text. Refer to the documentation
for the specific plugin to determine its capabilities and how to use them.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=242.Copy:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h3 res=506 name=pdf_form_fill-in
    x=left y=bottom width=100% height=100%.fill in PDF forms?
:p.:hp2.How do I...:ehp2.
:p.:hp2....fill in PDF forms?:ehp2.

:p.Filling in data in a PDF form is accomplished by simply typing in the
available fields on the form. Currently, when a document has been changed by
filling in any data (some or all fields), :hp2.Lucide:ehp2. will prompt to save
the document to a new filename upon closing or exiting the window.

:p.While pasting in :hp2.Lucide:ehp2. is generally not allowed, it is possible
to paste data from the system clipboard into form fields using the standard
OS/2 keyboard commands, along with :hp2.Ctrl+V:ehp2., :hp2.Ctrl+C:ehp2., and
:hp2.Ctrl+X:ehp2. may be used to copy and cut completed form data, in
addition to the conventional OS/2 :hp2.Ctrl+Ins:ehp2. and :hp2.Shift+Del:ehp2..

:p.:caution.For privacy and security concerns, do not edit an already-filled-in
document. Doing so will result in both the old and the new data being saved in
the resulting file, possibly exposing sensitive information. Always start with
a fresh PDF form. This is a known issue with the Poppler library which is
currently used by Lucide to render PDF documents.:ecaution.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=420.Mouse buttons and gestures:elink.
.br
:link reftype=hd res=400.Keyboard accelerators:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h3 res=508 name=controlling_remotely
    x=left y=bottom width=100% height=100%.control Lucide remotely?
:p.:hp2.How do I...:ehp2.
:p.:hp2....control Lucide remotely?:ehp2.

:p.Anything capable of piping data either locally or over the network should be
able to send commands to Lucide's PIPE. For a complete list of commands
recognized by Lucide, see :link reftype=hd res=440.Remote control
functions:elink.

:p.This can be useful for presentations with a remote control device, for
example.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=028.Navigation controls:elink.
:edl.


.* ............................................................................
:h3 res=510 name=opening_hyperlinks
    x=left y=bottom width=100% height=100%.configure Lucide to open hyperlinks?
:p.:hp2.How do I...:ehp2.
:p.:hp2....configure Lucide to open hyperlinks?:ehp2.

:p.Hyperlinks in PDF documents may lead to other points within the same
document, web content, email composition, or even other PDF documents. When the
mouse is hovering over one, the pointer changes to a hand :artwork runin
name='hand.bmp'. . Simply click to follow the link.

:p.To properly open web or email hyperlinks, it is necessary to ensure that the
default applications have been configured for the OS/2 Workplace Shell.
:hp2.Lucide:ehp2. will pass the location of the link to the configured
application.

:p.Hyperlinks targeted at other PDF documents may or may not behave as expected
due to a variety of factors, including what application was used to create the
current document and how the links were constructed. Better support for these
is planned.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=008.Document pane:elink.
.br
:link reftype=hd res=740.PDF hyperlinks:elink.
.br
:link reftype=hd res=217.Last link origin:elink.
:edl.


.* ............................................................................
:h3 res=512 name=disable_thumbnails
    x=left y=bottom width=100% height=100%.disable auto-creation of thumbnails?
:p.:hp2.How do I...:ehp2.
:p.:hp2....disable auto-creation of thumbnails?:ehp2.

:p.If so configured, upon opening a supported file, :hp2.Lucide:ehp2. creates
a thumbnail of the file and attempts to store that in the file's extended
attributes (assuming the file has been opened from writable media, the user has
rights to modify files on the volume, and the filesystem supports extended
attributes).

:p. This behavior may not always be desirable, however, such as when the
document contains sensitive information. To disable thumbnail creation by
default, check the appropriate box in the :link reftype=hd res=110.Settings
dialog:elink.. To disable thumbnail creation for a specific file (when
thumbnails have been so enabled), select the Toggle no thumbnail creation
checkbox in the :link reftype=hd res=102.Open File dialog:elink. when opening
the file.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=102.Open File dialog:elink.
.br
:link reftype=hd res=110.Settings dialog:elink.
.br
:link reftype=hd res=730.PDF security:elink.
.br
:link reftype=hd res=840.Security:elink.
.br
:link reftype=hd res=513.Removing thumbnails:elink.
:edl.


.* ............................................................................
:h3 res=513 name=remove_thumbnails
    x=left y=bottom width=100% height=100%.remove a thumbnail?
:p.:hp2.How do I...:ehp2.
:p.:hp2....remove a thumbnail?:ehp2.

:p.Earlier versions of :hp2.Lucide:ehp2. had no ability to disable the creation
of thumbnails. Thus, even for encrypted PDFs which may have contained sensitive
information, thumbnails may have been created. One method to remove them is to
use Heiko Nitzsche's excellent del_ea.cmd, available on Hobbes&colon.

:p.http&colon.//hobbes.nmsu.edu/h-search.php?key=del_ea&amp.pushbutton=Search

:p.Another method is to use OS/2's included EAUTIL.EXE with the /S option to
split the extended attributes off of the file, using the following syntax from
an OS/2 window or full-screen session&colon.

:p.[C&colon.\]EAUTIL /S &lt.:hp1.filename.ext:ehp1.&gt. nul

:p.There are many other ways of removing extended attributes (and thus,
thumbnails).

:caution.
If additional data has been stored in the file's extended
attributes, the above procedures will result in the loss of that data.
:ecaution.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=512.Disabling thumbnails:elink.
,br
:link reftype=hd res=102.Open File dialog:elink.
.br
:link reftype=hd res=110.Settings dialog:elink.
.br
:link reftype=hd res=730.PDF security:elink.
.br
:link reftype=hd res=840.Security:elink.
:edl.


.* ............................................................................
:h3 res=514 name=directing_output
    x=left y=bottom width=100% height=100%.direct print output and layout?
:p.:hp2.How do I...:ehp2.
:p.:hp2....direct print output and layout?:ehp2.

:p.From the :link reftype=hd res=104.Print dialog:elink., it is possible to
select the printer for producing output from the current document. Settings
for page ranges and even/odd pages are available in the dialog, but more
advanced settings should be selected at the job level. To do this, click the
Job properties button, which opens the system printer job settings notebook.
The print driver should provide for different page layout options (booklet,
2-up, 4-up, duplex, etc.).


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=024.Print...:elink.
.br
:link reftype=hd res=224.Print...:elink.
.br
:link reftype=hd res=104.Print dialog:elink.
:edl.


.* ............................................................................
:h3 res=580 name=get_help
    x=left y=bottom width=100% height=100%.get help with problems?
:p.:hp2.How do I...:ehp2.
:p.:hp2....get help with problems?:ehp2.

:p.:hp2.Lucide:ehp2. is a Netlabs project. The starting point for problem
resolution is the :hp2.Lucide:ehp2. wiki&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.If the problem you are experiencing has not been discussed in the wiki, feel
free to open a ticket in the bug tracker&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.or join the Lucide mailing list, by following the directions on the wiki.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=900.References:elink.
.br
:link reftype=hd res=582.Missing features:elink.
.br
:link reftype=hd res=584.Get involved with the project:elink.
:edl.


.* ............................................................................
:h3 res=582 name=feature_requests
    x=left y=bottom width=100% height=100%.make a feature request?
:p.:hp2.How do I...:ehp2.
:p.:hp2....make a feature request?:ehp2.

:p.:hp2.Lucide:ehp2. is a Netlabs project. The starting point for feature
requests is the :hp2.Lucide:ehp2. wiki&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.If the feature you are missing has not been discussed in the wiki, feel free
to make a request in the bug tracker&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.or join the Lucide mailing list, by following the directions on the wiki.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=900.References:elink.
.br
:link reftype=hd res=580.Problems:elink.
.br
:link reftype=hd res=584.Get involved with the project:elink.
:edl.


.* ............................................................................
:h3 res=584 name=get_involved
    x=left y=bottom width=100% height=100%.get involved with the Lucide project?
:p.:hp2.How do I...:ehp2.
:p.:hp2....get involved with the Lucide project?:ehp2.

:p.:hp2.Lucide:ehp2. is a Netlabs project. As such, it is an all-volunteer
effort. Aside from contributing code, documentation and translation work is
time consuming though extremely valuable to making :hp2.Lucide:ehp2. all that
it can be. Even contributing to content in the wiki is appreciated or
researching new and better ways to perform current tasks. The starting point
for involvement is the :hp2.Lucide:ehp2. wiki&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.Joining one of the Lucide mailing lists, by following the directions on the
wiki, is another great way to get started.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=900.References:elink.
.br
:link reftype=hd res=580.Problems:elink.
.br
:link reftype=hd res=582.Missing features:elink.
:edl.


.* ............................................................................
:h1 res=700 name=concepts
    x=left y=bottom width=100% height=100%.Concepts

:p.:hp2.Lucide:ehp2. is a plugin-based document viewer with support for various
file formats, primarily, Adobe's Portable Document Format (PDF). It provides
a SOM-based plugin architecture which allows third-party developers to easily
add plugins to support additional file formats.

:p.It is helpful to understand some of the concepts associated with the
different document types supported by :hp2.Lucide:ehp2. and how the program
presents the data differently based upon the document type.

:p.:ul compact.
:li.:link reftype=hd res=710.Types of PDF documents:elink.
:li.:link reftype=hd res=720.PDF forms:elink.
:li.:link reftype=hd res=730.PDF security:elink.
:li.:link reftype=hd res=740.PDF hyperlinks:elink.
:li.:link reftype=hd res=780.Image formats:elink.
:eul.


.* ............................................................................
:h2 res=710 name=pdf_types
    x=left y=bottom width=100% height=100%.Types of PDF documents

:p.:hp2.Lucide:ehp2. is capable of handling a variety of PDF types. It is
helpful to understand some of the differences between them.

:p.:ul compact.
:li.:link reftype=hd res=712.In general:elink.
:li.:link reftype=hd res=714.Font embedding vs substitution:elink.
:li.:link reftype=hd res=716.PDF variants:elink.
:eul.


.* ............................................................................
:h3 res=712 name=pdf_types_in_general
    x=left y=bottom width=100% height=100%.In general

:p.Portable Document Format files, or PDFs, generally fall into one of three
categories&colon.
.br
:ul compact.
:li.true or digitally created, meaning the source of the document was a word
processor or some other application which generated text and/or images as
"printed" output;
:li.imaged or scanned, implying that the document is essentially a picture of a
document, presented as an image file; or
:li.mixed, a document which started out as an image but was processed
after-the-fact to recognize and convert the image of the text to something
searchable.
:eul.

:p.PDF forms are variants of the first type, and can fall under yet another set
of groups. For a more detailed discussion of PDF forms, please see :link
reftype=hd res=720.PDF forms:elink., later.

:p.:hp2.Lucide:ehp2. can presently render all three of the main categories of
PDFs, with some exceptions. The range of acceptable forms is growing wider with
each release, however, so at some point, Lucide should be able to render all
types of PDFs, including the less common ones which currently may cause some
difficulty.


.* ............................................................................
:h3 res=714 name=pdf_fonts
    x=left y=bottom width=100% height=100%.Font embedding vs substitution

:p.A true PDF may handle fonts using one or more of the following methods&colon.

:p.:ul compact.
:li.substitution, which causes Lucide to render "on-the-fly" a general
representation using typeface information within the document;
:li.embedding, where all typefaces required to render a font are embedded
within the document;
:li.subsetting, where only the individual typeface characters required to
render the document are embedded.
:eul.

:p.Because a typeface may have thousands of characters, embedding only the
actual characters used in the specific document may result in a smaller file,
and usually, this is desirable.

:p.Substitution normally results in the smallest file sizes, however, it can
pose issues for archival purposes or other situations where absolute fidelity
of the source material is required. Non-standard fonts and, for example, math
symbols, may not render faithfully enough for proper representation of the
data.

:p.Embedding stores the entire typeface in the PDF document, usually resulting
in the largest filesize, though the most faithful to the source.

:p.Subsetting provides a balance between file size and fidelity, as it renders
all the characters used in the document accurately, while minimizing wasted
space in the file used by characters and typefaces which are not used in the
document.

:p.:hp2.Lucide:ehp2.'s bundled PDF plugin utilizes the :link refid=poppler
reftype=fn.Poppler library:elink. to render PDF documents. Poppler, in turn,
utilizes the same :link refid=fontconfig reftype=fn.Fontconfig library:elink.
as current Mozilla applications in order to perform font name substitution, so
that appropriate alternative fonts can be selected for documents without
embedded fonts.

:p.Depending upon the fonts currently installed on the system, some substituted
fonts may work better than others. Fontconfig makes a reasonable determination
when selecting an alternative font, however, the available selection is key.
Having a robust set of fonts installed on the system can make the difference
between a readable document or one which is either missing content or is
difficult - if not impossible - to read.

:p.In addition to rendering, it should be noted that full text search in
:hp2.Lucide:ehp2. is only possible with true or mixed PDF documents, where
actual text is available to be searched. This is not possible with image type
PDFs.


:fn id=poppler.
Poppler is a PDF rendering library based on the xpdf-3.0 code base.

:p.Homepage&colon.
.br
https&colon.//poppler.freedesktop.org/

:p.Bug reports against Poppler&colon.
.br
https&colon.//bugs.freedesktop.org/buglist.cgi?query_format=specific&amp.order=relevance+desc&amp.bug_status=__open__&amp.product=poppler&amp.content=

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/Poppler_%28software%29
:efn.

:fn id=fontconfig.
Fontconfig is a library for configuring and customizing font access.
:p.Homepage&colon.
.br
https&colon.//www.fontconfig.org/

:p.Bug reports against Fontconfig&colon.
.br
https&colon.//bugs.freedesktop.org/buglist.cgi?bug_status=__open__&amp.order=relevance%20desc&amp.product=fontconfig&amp.query_format=specific
:efn.



.* ............................................................................
:h3 res=716 name=pdf_variants
    x=left y=bottom width=100% height=100%.PDF variants

:p."PDF" is the common term used to describe all Portable Document Format
files, however, there are a number of subsets of the technology, and :link
refid=iso_32000-1 reftype=fn.the PDF standard itself:elink. has undergone
many changes throughout its history.

:p."Standard" (ISO 32000-1-compliant) PDF documents should generally be
readable by :hp2.Lucide:ehp2.. These documents allow for font embedding or
substitution, however, they may include some XFA (XML Forms Architecture)
elements which are not yet well-handled by Poppler, and thus, by extension,
:hp2.Lucide:ehp2.. For a more detailed discussion of PDF forms, please see
:link reftype=hd res=720.PDF forms:elink., later.

:p.:link refid=iso_19005 reftype=fn.PDF/A:elink. is a subset of PDF which
aims to eliminate certain risks to document fidelity. For example, PDF/A does
not allow dynamic content (substituted fonts or other media), which makes it
the format of choice for archival purposes. All data required to render the
document is contained in the PDF/A file, including fonts, color profiles,
images, etc.

:p.:hp2.Lucide:ehp2. should handle PDF/A documents as any others, though PDF/A
may tend to be larger in size than some others, and thus take a longer time to
load and require more processing power to navigate.

:p.:link refid=iso_24517-1 reftype=fn.PDF/E:elink., a subset of PDF, was
designed for engineering and technical documentation. It is based on the PDF
Reference version 1.6 from Adobe Systems and supports interactive media,
including 3D images and animation.

:p.:link refid=iso_14739-1 reftype=fn.PRC:elink. (Product Representation
Compact) is defined within PDF/E-2 as a highly compressed file format for 3D
content, designed to be included in PDF and other similar document formats for
the purpose of 3D visualization and exchange. It can be used for creating,
viewing, and distributing 3D data in document exchange workflows. It is
optimized to store, load, and display various kinds of 3D data, especially that
coming from computer aided design (CAD) systems.

:p.:link refid=ecma-363 reftype=fn.U3D:elink. is another compressed file format
able to be utilized by PDF/E. U3D is a standard published and maintained by
ECMA International as ECMA-363.

:p.:hp2.Lucide:ehp2. should be able to open 2D PDF/E documents as expected,
though media content will not be playable. Likewise, embedded 3D files, either
U3D or PRC format, will not be rendered. Additionally, only a single layer of
multi-layered PDF/E documents will be rendered.

:p.:link refid=iso_14289-1 reftype=fn.PDF/UA:elink. (Universal Access) provides
accessibility for people with disabilities using screen readers, screen
magnifiers, joysticks, etc. to navigate and read electronic documents.

:p.:hp2.Lucide:ehp2. is able to render the textual content of PDF/UA
documents, though :hp2.Lucide:ehp2. currently lacks any type of facility
for passing along linked data to a screen reader, for example. Text in a PDF/UA
document appears as one large link to :hp2.Lucide:ehp2., and the mouse pointer
will appear continually as a hand :artwork runin name='hand.bmp'. .

:p.:link refid=iso_16612-2 reftype=fn.PDF/VT:elink. (Variable and
Transactional) is built on PDF/X-4 and PDF/X-5, utilizing PDF 1.6. It is the
first variable-data printing (VDP) format which ensures modern :link refid=icc
reftype=fn.ICC-based:elink. color management utilizing ICC Output Intents. It
adds the concept of encapsulated groups of graphical objects to support
optimized efficient processing for repeating text or image content. Through
Document Part Metadata (DPM), reliable and dynamic management of pages for High
Volume Transactional Output (HVTO) print data is achieved, e.g., record
selection or postage optimization based on such metadata.

:p.PDF/VT-1 always consists of a single, self-contained file, though other
variants of the standard allow external graphic content (PDF/VT-2), and
PDF/VT-2s provides for streaming through the use of multi-part MIME packages.
Such documents may be be shared, viewed, and navigated interactively using
standard PDF reader software (such as :hp2.Lucide:ehp2.), however true fidelity
requires PDF/X-4 or PDF/VT-conforming software (a future release of Poppler may
be fully compliant).

:p.Due to the fully-embedded nature of PDF/VT-1 documents, :p.:hp2.Lucide:ehp2.
is able to render these faithfully, however PDF/VT-2 (and by extension,
PDF/VT-2s) will only render the selected document and not any of its
externally-linked component documents. This may be addressed in a future
Poppler release.

:p.:link refid=iso_15930 reftype=fn.PDF/X:elink. is similar to PDF/A in that it
also must contain embedded data, however, as the main purpose of PDF/X is to
handle exchange of graphics, it has a number of print-related requirements
beyond the scope of standard PDFs. In addition to embedding images, when
conforming to the PDF/X-1a specification (originally based on PDF 1.3, with the
2003 update based on PDF 1.4), such images must be CMYK or spot colors.
Calibrated RGB and CIELAB colors are acceptable when conforming to PDF/X-3
(based on PDF 1.4), though most of the other requirements of PDF/X-1a remain.
(PDF/X-2 was never published.)

:p.PDF/X-4 provides color-managed, CMYK, gray, RGB, or spot color
data support, in addition to transparency and optional content, where all
content is provided within the file. A second conformance level (PDF/X-4p,
based on PDF 1.6) is used to designate a PDF/X-4 document where a
required ICC profile is externally supplied and unambiguously identified.

:p.PDF/X-5 (based on PDF 1.6) allows for all data to be included or where
provision has been made for unique identification of externally supplied
graphical content or n-colorant ICC profiles. This standard was updated in
2010 with minor corrections which did not alter the original specification.

:p.PDF/X-5 provides for three levels of conformance&colon.

:p.:ul.
:li.PDF/X-5g&colon., which extends PDF/X-4, enabling the use of external
graphical content (OPI-like - Open Prepress Interface - workflows). More
specifically, graphics may be referenced which are outside the PDF, which "can
have value in reducing ... demands ... by allowing ... work with low
resolution" [ISO-15930-8&colon.2010].

:li.PDF/X-5pg&colon., which extends PDF/X-4p, enabling the use of external
graphical content in conjunction with a reference to an external ICC Profile
for the output intent.

:li.PDF/X-5n&colon., which extends PDF/X-4p, enabling an externally-supplied
ICC Profile for the output intent to use a color space other than Grayscale,
RGB, or CMYK.
:eul.

:p.PDF/X must also include a special file identification, stating with which
PDF/X version they are compliant. A given file may conform only to a single
PDF/X standard.

:p.:hp2.Lucide:ehp2. should be able to open PDF/X documents as well as PDF/A,
as the embedded content should be fully supported by Poppler.

.* ............................................................................
:fn id=icc.
The International Color Consortium&lnotrev. profile format provides a cross-
platform device profile format. Device profiles can be used to translate color
data created on one device into another device's native color space. The
acceptance of this format by operating system vendors allows end users to
transparently move profiles and images with embedded profiles between different
operating systems.

:p.The International Color Consortium&colon.
.br
http&colon.//www.color.org/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/International_Color_Consortium
:efn.

.* ............................................................................
:fn id=iso_32000-1.
While originally developed by Adobe Systems, since 2008, PDF as a standard has
been maintained by the ISO as ISO 32000-1&colon.2008. The complete text of the
standard is available from&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=51502

:p.PDF is overseen by the PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/Portable_Document_Format
:efn.

.* ............................................................................
:fn id=iso_19005.
PDF/A is an ISO standard which has so far received three major revisions&colon.
.br
PDF/A-1&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=60603
.br
PDF/A-2&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=50655
.br
PDF/A-3&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=57229

:p.PDF/A is overseen by the PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/A
:efn.

.* ............................................................................
:fn id=iso_24517-1.
ISO 24517-1&colon.2008 is based on PDF Reference version 1.6 from Adobe Systems
&colon.
.br
https&colon.//www.adobe.com/devnet/pdf/pdf_reference_archive.html

:p.The ISO standards document is located here&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=42274

:p.PDF/E is overseen by the PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/E
:efn.

.* ............................................................................
:fn id=iso_14739-1.
PRC (ISO 14739-1&colon.2014) is defined as part of the PDF/E-2.

:p.The ISO standards document is located here&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=54948

:p.PRC is overseen by the 3DPDF Consortium&colon.
http&colon.//www.3dpdfconsortium.org/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/PRC_%28file_format%29
:efn.

.* ............................................................................
:fn id=ecma-363.
U3D (ECMA-363) is a file format for 3D content, which, like PRC, is able to be
embedded in PDF/E-2 documents.

:p.The EMCA International standards document is located here&colon.
.br
http&colon.//www.ecma-international.org/publications/standards/Ecma-363.htm

:p.U3D is overseen by the 3DPDF Consortium&colon.
http&colon.//www.3dpdfconsortium.org/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/Universal_3D
:efn.

.* ............................................................................
:fn id=iso_14289-1.
ISO 14289-1&colon.2014, the second revision of the standard originally released
in 2012, is the first freely available standards document from the ISO, and is
itself a PDF/UA document&colon.
.br
http&colon.//www.iso.org/iso/catalogue_detail.htm?csnumber=54564

:p.PDF/UA is overseen by the PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.The PDF Association also maintains a compliance test suite for PDF/UA,
called The Matterhorn Protocol&colon.
.br
http&colon.//www.pdfa.org/publication/the-matterhorn-protocol-1/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/UA
:efn.

.* ............................................................................
:fn id=iso_16612-2.
PDF/VT-2&colon.2010 (which encompasses PDF/VT-1) is an ISO standard&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=46428

:p.PDF/VT is overseen by the PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/VT
:efn.

.* ............................................................................
:fn id=iso_15930.
PDF/X is an ISO standard which has so far received several revisions and
extensions&colon.
.br
PDF/X-1&colon.2001&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=29061
.br
PDF/X-1a&colon.2003&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=39938
.br
PDF/X-3&colon.2002&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=34941
.br
PDF/X-3&colon.2003&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=39940
.br
PDF/X-4&colon.2008&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=42876
.br
PDF/X-4&colon.2010&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=55843
.br
PDF/X-5&colon.2008&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=42877
.br
PDF/X-5&colon.2010&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=55844

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/X
:efn.


.* ............................................................................
:h2 res=720 name=pdf_forms
    x=left y=bottom width=100% height=100%.PDF forms

:p.Fillable PDFs consist of two main types&colon.

:ul.
:li.AcroForms, typically created using versions of Adobe Acrobat 4.x through
7.x
:li.XFA-based (XML Forms Architecture) forms, developed by a Accellio, which
was subsequently acquired by Adobe. These documents store the XML data
structure inside the PDF, and are now the standard method for creating PDF form
documents. Adobe LiveCycle Designer 7.x and newer, as well as Acrobat newer
than 7.x create XFA-based forms.
:eul.

:p.:hp2.Lucide:ehp2. is capable of handling both types of PDF forms, though
with some caveats. When saving form data to an XFA-based document, the Poppler
library used by :hp2.Lucide:ehp2. stores the user-supplied entries in the PDF,
and :hp2.Lucide:ehp2., upon detecting a change to the original document,
prompts the user to save the file under a different name.

:p.:caution.Subsequently editing the previously-saved form will result in the
new data being stored along with the old data, and the old data is not removed
from the file. This may present a security risk. For this reason, it is
strongly advised to only save data into an unused PDF form, and to not simply
re-use an existing, partially or completely filled-in form for editing.:ecaution.

:p.Other related types of documents for handling form data are FDF (Forms Data
Format) and XFDF (XML Forms Data Format). Currently, :hp2.Lucide:ehp2. is not
capable of handling either of these formats due to lack of support in Poppler.

:p.Newer versions of Acrobat may also employ JavaScript elements in the PDF for
such things as dropdown lists and other conditional data presentation.
:hp2.Lucide:ehp2. currently does not handle these types of fields, though it
may render the rest of the document faithfully, and even allow input to any
other form fields. It is advised not to utilize :hp2.Lucide:ehp2. for these
documents. This limitation may be addressed in a future release of the Poppler
library.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=720.PDF Forms:elink.
.br
:link reftype=hd res=219.Save...:elink.
.br
:link reftype=hd res=220.Save as...:elink.
.br
:link reftype=hd res=506.How do I...fill in PDF forms?:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
:edl.


.* ............................................................................
:h2 res=730 name=pdf_security
    x=left y=bottom width=100% height=100%.PDF security

:p.The PDF standard provides for several different types and levels of
security in documents&colon.

:ul.
:li.Encrypted passwords
:li.Certificate security
:li.Secure PDF envelopes
:li.Permissions
:eul.

:p.Passwords for opening PDF documents (generally known as owner passwords) are
currently encrypted using either 40-bit or 128-bit :link refid=rc4
reftype=fn.RC4:elink. (considered weak by today's standards, even in the
128-bit variant) or, in documents created by newer versions of Acrobat or other
tools, 128-bit or 256-bit :link refid=aes reftype=fn.AES:elink..

:p.:hp2.Lucide:ehp2. is capable of decrypting both types of passwords,
including those encrypted using the latest AES 256-bit cipher.


:hp2.
:table cols='30 15 15'.
:row.
:c.PDF revision (Acrobat version)
:c.Encryption algorithm &amp. length
:c.Max password length
:row.
:c.PDF 1.1 - 1.3 (Acrobat 2-4)
:c.RC4 40-bit
:c.32 characters (Latin-1)
:row.
:c.PDF 1.4 (Acrobat 5)
:c.RC4 128-bit
:c.32 characters (Latin-1)
:row.
:c.PDF 1.5 (Acrobat 6)
:c.RC4 128-bit
:c.32 characters (Latin-1)
:row.
:c.PDF 1.6 (Acrobat 7) &amp. PDF 1.7 (ISO 32000-1) (Acrobat 8)
:c.AES-128
:c.32 characters (Latin-1)
:row.
:c.PDF 1.7 Adobe Extension Level 3 (Acrobat 9)
:c.AES-256
:c.127 UTF-8 bytes (Unicode)
:row.
:c.PDF 1.7 Adobe Extension Level 8 (Acrobat X/XI/DC) &amp. (anticipated) PDF
2.0 (ISO 32000-2 (specification not yet finalized)
:c.AES-256
:c.127 UTF-8 bytes (Unicode)
:etable.
:ehp2.


:p.Digital certificates (self-signed or from trusted third parties) may be
used to encrypt (using the same algorithms available for encrypting passwords)
or to digitally "sign" documents. Such digital signatures are considered
legally binding in many jurisdictions.

:p.Currently, :hp2.Lucide:ehp2. has no method for handling certificate
security, although a document which has been signed with a digital ID may be
read (and the digital signature and stamp displayed) as long as it has not
also been encrypted with a certificate.

:p.Secure PDF envelopes are essentially bundles of files enclosed within (or
rather, attached to) a PDF, which serves as a wrapper (or cover page). The
envelope is may then be password protected and optionally signed, and the
contents password protected.

:p.If the envelope is unencrypted or encrypted with a password,
:hp2.Lucide:ehp2. will be able to open the envelope PDF itself. The contents,
or file attachments, - which may be of any type - will not be accessible,
however.

:p.Permissions include restrictions on printing and copying content (to the
system clipboard or otherwise saving a document as another file), as well as
allowing access by screen readers, etc.

:p.Document permissions are set in the PDF at the time of creation, and
normally require a separate password to bypass their restrictions. The Poppler
library used by :hp2.Lucide:ehp2. ignores such restrictions and does not
prompt for password input to bypass them.


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=840.Security:elink.
.br
:link reftype=hd res=710.Types of PDF documents:elink.
.br
:link reftype=hd res=220.Save as...:elink.
:edl.


.* ............................................................................
:fn id=rc4.
RC4 (Rivest Cipher 4), once known for its elegance and speed, has been rendered
generally unusable as a strong cryptographic cipher. When the beginning of the
output keystream is not discarded, or when there is a lack of sufficient
entropy in the keys used, it is particularly vulnerable to compromise. It is
recommended that if security is a real concern, RC4 ciphers (even at 128-bit)
not be used.

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/RC4
:efn.


.* ............................................................................
:fn id=aes.
Advanced Encryption Standard (AES), or Rijndael, developed by two Belgian 
cryptographers, Joan Daemen and Vincent Rijmen, was adopted by the U.S.
National Institute of Standards and Technology (NIST) in 2001 as FIPS PUB 197
(FIPS 197).

:p.NIST utilizes three different ciphers for AES, each with a block size of
128 bits, but with three different key lengths (128, 192, and 256 bits).

:p.The algorithm described by AES is symmetric-key (i.e., the same key is used
for both encrypting and decrypting the data). 

:p.AES is currently considered the best means to encrypt data for transmission
either in transit or in storage.

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/Advanced_Encryption_Standard
:efn.



.* ............................................................................
:h2 res=740 name=pdf_hyperlinks
    x=left y=bottom width=100% height=100%.PDF hyperlinks

:p.Hyperlinks within PDF documents may reference other parts of the same
document, other documents, or may open external programs (such as for sending
email or visiting a website).

:p.Depending upon the type of hyperlink, :hp2.Lucide:ehp2. may or may not
handle it as expected. Links within documents should work, as should web links.
(see :link reftype=hd res=510.Opening hyperlinks:elink. for more discussion).


:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=510.Opening hyperlinks:elink.
.br
:link reftype=hd res=217.Last link origin:elink.
:edl.


.* ............................................................................
:h2 res=780 name=img_formats
    x=left y=bottom width=100% height=100%.Image formats

:p.:hp2.Lucide:ehp2.'s included plugins for handling image formats accept the
following types of files&colon.

:p.Due to :hp2.Lucide:ehp2.'s plugin-based architecture, it is possible to
create one or more plugins to support a variety of additional formats or to
replace one or more of the included plugins with something more robust. 

:p.The Generalized Bitmap Module (:link refid=gbm reftype=fn.GBM:elink.) 
which is capable of rendering BMP, JPG, JP2, PNG, TIF, PBM, PGM, PPM, PNM, 
XPM, JBG and RAW formats is now part of the :hp2.Lucide:ehp2. package. Many
thanks to Heiko Nitzsche its developer for permitting us to include it.
It should be used as a replacement for :hp2.Lucide:ehp2.'s JPG plugin. 

:p.:hp2.Lucide:ehp2. utilizes DjVuLibre for its 
:link refid=djvu reftype=fn.DjVu:elink. plugin. To
:hp2.Lucide:ehp2., all DjVu files are images, even when they contain an OCR
layer. Thus, DjVu document images are not searchable.

:p.The :link refid=jpeg reftype=fn.JPEG:elink. (JPG) plugin should not be 
installed with the GBM plugin which also provides JPG support. The JPG 
plugin isn't installed by default in 1.5.0. However it was in earlier
versions so you should either uninstall earlier versions before installing
1.5.0 (preferred) or you should delete or rename lujpeg.dll.

:dl tsize=10 break=none.
:dt.:hp2.Related&colon.:ehp2.
:dd.:link reftype=hd res=900.References:elink.
.br
:link reftype=hd res=580.Problems:elink.
.br
:link reftype=hd res=582.Missing features:elink.
:edl.


.* ............................................................................
:fn id=jpeg.
An an acronym for the Joint Photographic Experts Group, which created the
format, JPEG (also known by its common file extension, "JPG") provides lossy,
adjustable compression for digital images, and is particularly suited for
digital photographs. JPEG can usually achieve 10&colon.1 compression with
before there is a perceptible loss in image quality (to the naked eye).

:p.Several variants of JPEG exist, the most common of which is JPEG/Exif, as
that is used by digital cameras and similar image-capturing devices, though all
variants are commonly called JPEG.

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/JPEG
:efn.


.* ............................................................................
:fn id=gbm.
GBM (Generalized Bitmap Module) is a library for handling many different
bitmap file formats. It comes with a set of useful command line tools for doing
bitmap manipulations and format conversion. In this version BMP, JPG, JP2, PNG,
TIF, PBM, PGM, PPM, PNM, XPM, JBG and RAW support is additionally included.

:p.The complete package is available on Hobbes&colon.
http&colon.//hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

:p.Homepage&colon.
.br
http&colon.//heikon.home.tlink.de/frames/gbm_plugin_lucide.html
:efn.


.* ............................................................................
:fn id=djvu.
Originally developed by Yann LeCun, L‚on Bottou, Patrick Haffner, and Paul G.
Howard at AT&amp.T Labs from 1996-2001, DjVu is a compression technique
and an archival document format specifically designed for digital libraries of
print originals, scanned or digitally produced. For scanned originals, DjVu
files are typically 3-10 times smaller than black &amp. white TIFF or PDF, and
5-10 times smaller than color JPEGs of similar resolution.

:p.DjVu files may contain an OCR text layer, where the original scan of textual
content has been converted to recognizable characters, searchable - and able to
be copied - by some viewers.

:p.Due to their smaller size as compared to PDF, DjVu documents are uniquely
suited to web distribution, particularly over low bandwidth connections.

:p.Wikipedia page&colon.
.br
https&colon.//en.wikipedia.org/wiki/DjVu
:efn.


.* ............................................................................
:h1 res=800 name=approach
    x=left y=bottom width=100% height=100%.Approach

:p.:hp2.Lucide:ehp2.'s plugin-based architecture provides a modular framework
for adding support for new file formats, and its SOM-based plugin architecture
allows third-party developers to easily build new plugins.

:p.This section of the user's guide discusses :hp2.Lucide:ehp2.'s design
philosophy, and how the pieces fit together.

:p.:ul compact.
:li.:link reftype=hd res=820.Plugin architecture:elink.
:li.:link reftype=hd res=830.Included plugins:elink.
:li.:link reftype=hd res=840.Security:elink.
:eul.


.* ............................................................................
:h2 res=820 name=plugin_architecture
    x=left y=bottom width=100% height=100%.Plugin architecture

:p.:hp2.Lucide:ehp2.'s plugin architecture utilizes SOM (System Object Model)
to ease the development of new plugins to enhance :hp2.Lucide:ehp2.'s
capabilities.

:p.Plugins may be created from a variety of sources, and loaded by
:hp2.Lucide:ehp2. at program startup. All functions configured in the
plugin become available to :hp2.Lucide:ehp2., including file information
detail to be displayed and search capabilities.

:p.New plugins may be requested through the :hp2.Lucide:ehp2. project page
&colon.
.br
https&colon.//trac.netlabs.org/lucide/

or may be developed completely independent of :hp2.Lucide:ehp2. itself, by any
capable third party.

:p.:hp2.Lucide:ehp2.'s dual licensing also allows for commercial plugin
development.


.* ............................................................................
:h2 res=830 name=included_plugins
    x=left y=bottom width=100% height=100%.Included plugins

:p.:hp2.Lucide:ehp2. is provided with plugins for viewing PDF, DjVu documents
and a wide range of bimap image formats using the GBM plugin. While a plugin
for viewing JPG images is still included we recommend that you install the GBM
plugin which provides JPG support and don't install or uninstall the JPG
plugin. We have seen some file open issues when 2 plugins that handle the 
same format are both installed.

:p.For more information on available plugins, see :link reftype=hd
res=780.Image formats:elink..


.* ............................................................................
:h2 res=840 name=security
    x=left y=bottom width=100% height=100%.Security

:p.The :hp2.Lucide:ehp2. project takes document security seriously. The
automatic disabling of thumbnail creation for encrypted documents, and the
ability to completely disable thumbnail creation by default are two examples of
this commitment to user security.

:p.:hp2.Lucide:ehp2. does not store passwords or any other personal information
about the user, nor does it cache metadata of opened or browsed documents of
any kind. Thumbnails, when created, are completely separate from
:hp2.Lucide:ehp2., and may be removed at any time.

:p.:hp2.Lucide:ehp2. has no facility for removing passwords from encrypted
files.

:p.If you have any concerns about privacy or security, please open a ticket on
the :hp2.Lucide:ehp2. project page&colon.
.br
https&colon.//trac.netlabs.org/lucide/


.* ............................................................................
:h1 res=880 name=env_vars
    x=left y=bottom width=100% height=100%.Environment variables

:p.:hp2.Lucide:ehp2. looks for the following environment variables upon program
start:

:ul compact.
:li.:hp2.LUCIDEINSTALLPATH:ehp2. tells :hp2.Lucide:ehp2. where it may find its
files.
:li.:hp2.LUCIDEHELP:ehp2. is a concatenated list of help files, beginning with
:hp2.Lucide:ehp2.'s own help file, to be opened when accessing Help from within
the program. Plugins should append their own help files to this list (via "+").
:eul.

:p.If these variables do not exist in CONFIG.SYS at the time of install, they
will be created. If they do already exist, they will be preserved.


.* ............................................................................
:h1 res=900 name=refs
    x=left y=bottom width=100% height=100%.References

:p.The following links should provide a starting point for further information
on :hp2.Lucide:ehp2.&colon.

:nt.Some links may not be accessible on all systems.:ent.

:ul compact.
:li.:hp2.Lucide:ehp2. wiki&colon. https&colon.//trac.netlabs.org/lucide/
:p.
:hp2.PDF&colon.:ehp2.
:li.3DPDF Consortium&colon. http&colon.//www.3dpdfconsortium.org/
:li.Adobe Systems Incorporated&colon. https&colon.//www.adobe.com
:li.PDF Association&colon. http&colon.//www.pdfa.org/
:li.PDFlib knowledge base&colon. 
https&colon.//www.pdflib.com/en/knowledge-base/
:li.Poppler project&colon. https&colon.//poppler.freedesktop.org/
:li.Poppler bugs (open)&colon. 
https&colon.//bugs.freedesktop.org/buglist.cgi?bug_status=__open__&amp.no_redirect=1&amp.order=Importance&amp.product=poppler&amp.query_format=specific
:p.
:hp2.DjVu&colon.:ehp2.
:li.DjVuLibre&colon. https&colon.//djvu.sourceforge.net/index.html
:li.DjVu.org&colon. http&colon.//www.djvu.org/
:li.DjVu.com&colon. http&colon.//djvu.com/
:p.
:hp2.JPEG and other image formats&colon.:ehp2.
:li.Independent JPEG Group http&colon.//www.ijg.org/files/
:li.Generalized Bitmap Module&colon. 
http&colon.//heikon.home.tlink.de/frames/gbm_plugin_lucide.html
:p.
:hp2.General&colon.:ehp2.
:li.Hobbes archive&colon. http&colon.//hobbes.nmsu.edu/
:li.International Organization for Standardization (ISO)&colon. 
http&colon.//www.iso.org/iso/home.htm
:li.EMCA International&colon. 
http&colon.//www.ecma-international.org/
:eul.


.* ............................................................................
:h1 res=950 name=notices
    x=left y=bottom width=100% height=100%.Notices

:p.Copyright &bx0012. 2016 netlabs.org in cooperation with Arca Noae, LLC,
formerly
.br
Copyright &bx0012. Eugene Romanenko, Dmitriy Kuminov, Silvan Scherrer, bww
bitwise works GmbH in cooperation with Mensys

:p.Other copyrights are the property of their respective owners.

.* ............................................................................
:h1 res=960 name=appendix
    x=left y=bottom width=100% height=100%.Appendix

:p.Plugins which provide their own help will appear after this page and should
be listed in the Contents of this guide.
:p.
:euserdoc.
