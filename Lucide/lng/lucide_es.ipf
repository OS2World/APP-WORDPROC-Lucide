:userdoc.
:docprof toc=123456.
:title.Manual del Usuario de Lucide
.* rev 2016-10-17-001
.* ----------------------------------------------------------------------------
:h1 res=001 name=intro
    x=left y=bottom width=100% height=100%.Sobre Lucide

:artwork align=center name='lucidelogo.bmp'.
:hp2.Lucide:ehp2. es un visor de documentos de arquitectura modular con soporte
para diversos formatos de archivo, principalmente el PDF (Portable Document
Format) de Adobe. Ofrece una arquitectura de m¢dulos basados en SOM que
permite a terceros programadores a§adir f†cilmente m¢dulos con los que dar
soporte a formatos de archivo adicionales.

:ul compact.
:li.:link reftype=hd res=002.Licencia:elink.
:li.:link reftype=hd res=003.Agradecimientos:elink.
:li.:link reftype=hd res=004.Inicio del programa:elink.
:li.:link reftype=hd res=1005.Soporte de idiomas:elink.
:li.:link reftype=hd res=005.Interfaz:elink.
:li.:link reftype=hd res=006.Paneles:elink.
:li.:link reftype=hd res=020.Barra de herramientas:elink.
:li.:link reftype=hd res=100.Di†logos y listas:elink.
:li.:link reftype=hd res=200.Men£s:elink.
:li.:link reftype=hd res=400.Teclas de funci¢n:elink.
:li.:link reftype=hd res=500.®C¢mo se...:elink.
:li.:link reftype=hd res=700.Conceptos:elink.
:li.:link reftype=hd res=800.Enfoque:elink.
:li.:link reftype=hd res=900.Referencias:elink.
:li.:link reftype=hd res=950.Avisos:elink.
:li.:link reftype=hd res=960.ApÇndice:elink.
:eul.

.* ............................................................................
:h2 res=002 name=license
    x=left y=bottom width=100% height=100%.Licencia

:hp2.Lucide:ehp2. se publica bajo licencia dual CDDL (COMMON DEVELOPMENT AND
DISTRIBUTION LICENSE) versi¢n 1.0 y LPGL (LESSER GENERAL PUBLIC LICENSE) de GNU
versi¢n 2.1.

:p.Los m¢dulos de Lucide se publican bajo licencia CDDL/LGPL o GPL, dependiendo
de cada caso. Consulte http&colon.//svn.netlabs.org/lucide/ para m†s
informaci¢n y acceder al c¢digo fuente.

:p.Nota para usuarios hispanohablantes&colon.

:p.La Fundaci¢n de Software Libre (FSF) no aprueba el uso oficial de
traducciones de sus licencias debido a los costes de verificaci¢n, as° como
para prevenir posibles responsabilidades legales derivadas del uso de
traducciones sin verificar, y hay problemas similares con la CDDL. Para su
comodidad, y de forma legalmente no vinculante, puede leer las licencias CDDL y
LGPL en espa§ol en los siguientes enlaces:

:ul compact.
:li.LGPL
:ul compact.
:li.https&colon.//gugs.sindominio.net/licencias/lgpl-es.html
:li.https&colon.//www.ecured.cu/LGPL
:eul.
:li.CDDL:
http&colon.//catux.org/posts/publicacie-la-nueva-licencia-de-software-libre-lpo.html
:eul.

:p.A continuaci¢n encontrar† las licencias legalmente vinculantes en el inglÇs
original&colon.

:p.
.ce COMMON DEVELOPMENT AND DISTRIBUTION LICENSE (CDDL) Version 1.0

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
    x=left y=bottom width=100% height=100%.Agradecimientos

Lucide ha sido escrito y mantenido por&colon.

:p.Eugene Romanenko, netlabs.org
.br
Dmitriy Kuminov, netlabs.org
.br
en colaboraci¢n con Serenity Systems International

:p.Gregg Young
.br
Andy Willis
.br
Steven Levine
.br
Matthias Waltenberger
.br
Ronald Brill
.br
Lewis Rosenthal
.br
un equipo de traductores y contribuidores
en colaboraci¢n con Arca Noae, LLC

.* ----------------------------------------------------------------------------
:h1 res=004 name=program_start
    x=left y=bottom width=100% height=100%.Inicio del programa

Lucide puede iniciarse desde el objeto del escritorio, bien por s° mismo, o
arrastrando hasta Çl un archivo de un tipo soportado, o desde un indicador de
mandatos, tanto especificando el nombre del programa solo como acompa§†ndolo
del nombre de un documento de un tipo soportado para que lo abra.

:dl tsize=10 break=none.
:dt.:hp2.Ejemplo:ehp2.
:dd.:hp2.[C&colon.\PROGRAMAS\Lucide]Lucide c&colon.\directorio\documento.pdf:ehp2.
:edl.


:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=228.Salir:elink.
:edl.

.* ----------------------------------------------------------------------------
:h1 res=1005 name=language_support
    x=left y=bottom width=100% height=100%.Soporte de Idiomas

Lucide soporta 12 idiomas en diferentes grados. El instalador s¢lo instala
el idioma definido por la variable de entorno LANG, que se establece en
config.sys, o inglÇs si el idioma definido no es uno de los soportados.

:p.Si instala diversos paquetes de idioma, Lucide cargar† el definido en la
variable LANG si est† entre ellos. DespuÇs recurrir† al inglÇs (Lucide.lng) si
se instal¢. Por £ltimo buscar† cualquier archivo Lucide_xx.lng que haya
instalado en el siguiente orden: {de, es, fr, it, sv, da, nl, ru, pl, cs, zh}
cargando el primero de ellos que encuentre. Puede utilizar cualquier idioma
soportado en cualquier sistema instalando Æs¢loØ ese idioma. Lucide 1.40
instalaba el inglÇs por omisi¢n, de modo que deber°a desinstalarlo primero o
hacer planes de borrar Lucide.lng si desea utilizar un idioma que no sea el
inglÇs ni el del sistema.

:p.Debido a la falta de traducciones actualizadas para todos los idiomas
excepto el espa§ol (el alem†n es el siguiente m†s completo), se instalan las
versiones inglesas de la ayuda principal, la de GBM, el archivo lÇame principal
y el de LUGMB, el historial de cambios y lugbm.cfg. Los archivos lugbm_xx.cfg
traducidos se cargan antes que lugbm.cfg si est†n instalados. Si se han
instalado varios archivos lugbm_xx.cfg se carga el primero que se encuentre
seg£n el orden establecido antes.

.* ----------------------------------------------------------------------------
:h1 res=005 name=interface
    x=left y=bottom width=100% height=100%.Interfaz

La aplicaci¢n se ha dise§ado con dos paneles, un :link reftype=hd res=007.panel
de navegaci¢n:elink. opcional a la izquierda para proporcionar una lista de
marcadores pulsables para desplazarse f†cilmente de un lugar a otro del
documento, que se muestra en :link reftype=hd res=008.su propio panel:elink., el
principal y situado a la derecha, por el que se puede desplazar el contenido
mostr†ndolo con el tama§o seleccionado.

:p.Entre el :link reftype=hd res=007.panel de navegaci¢n:elink. y el :link
reftype=hd res=008.panel de contenido:elink. hay una barra divisora m¢vil,
junto a la cual tambiÇn se encuentra la barra de desplazamiento del :link
reftype=hd res=007.panel de navegaci¢n:elink. cuando es necesaria. Arrastrar la
barra divisora a izquierda o derecha establecer† su posici¢n hasta que cierre
:hp2.Lucide:ehp2.. Al cerrar la £ltima ventana de :hp2.Lucide:ehp2. que
quede abierta se guardar† la posici¢n de la barra. Las ventanas de
:hp2.Lucide:ehp2. abiertas desde el submen£ :link reftype=hd res=212.Nueva
ventana:elink. del :link reftype=hd res=210.men£ Archivo:elink. heredan la
posici¢n de su barra divisora de la ventana actual.

:p.El :link reftype=hd res=200.men£:elink. proporciona navegaci¢n general y
algunas funciones no disponibles a travÇs del :link reftype=hd res=211.men£ de
contexto:elink. o los botones de la barra de herramientas.

:p.El £ltimo componente de la interfaz de usuario es la :link reftype=hd
res=020.barra de herramientas:elink., que proporciona acceso inmediato a
operaciones comunes y un selector desplegable para el tama§o del documento.

:ul compact.
:li.:link reftype=hd res=006.Paneles:elink.
:li.:link reftype=hd res=007.Panel de navegaci¢n:elink.
:li.:link reftype=hd res=008.Panel de contenido:elink.
:li.:link reftype=hd res=020.Barra de herramientas:elink.
:li.:link reftype=hd res=100.Di†logos y contenedores:elink.
:li.:link reftype=hd res=200.Men£s:elink.
:li.:link reftype=hd res=400.Teclas de funci¢n:elink.
:eul.

.* ............................................................................
:h2 res=006 name=panes
    x=left y=bottom width=100% height=100%.Paneles

El :link reftype=hd res=007.panel de navegaci¢n:elink. est† a la izquierda
propocionando una lista de marcadores pulsables para desplazarse f†cilmente de
un lugar a otro. Se puede activar y desactivar con la :link reftype=hd
res=400.tecla r†pida F9:elink., el bot¢n
:artwork runin name='navpanel.bmp'.
:artlink.
:link reftype=hd res=020.
:eartlink. de la barra de herramientas o el men£ Ventana. Si se desactiva,
el :link reftype=hd res=008.panel de contenido:elink. se ensancha hasta llenar
la ventana del programa.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=007.Panel de navegaci¢n:elink.
.br
:link reftype=hd res=008.Panel de contenido:elink.
.br
:link reftype=hd res=020.Barra de herramientas:elink.
:edl.

.* ............................................................................
:h3 res=007 name=nav_pane
    x=left y=bottom width=100% height=100%.Panel de navegaci¢n

El panel de navegaci¢n muestra los marcadores definidos (al crearse en un
documento soportado) o una lista de p†ginas. Los marcadores pueden aparecer
anidados, con el bot¢n :artwork runin name='expand.bmp'. para expandirlos
y :artwork runin name='collapse.bmp'. para colapsarlos.

:p.En los documentos que no tengan marcadores definidos, el panel de navegaci¢n
mostrar† :hp2.P†gina 1:ehp2., :hp2.P†gina 2:ehp2., etc. Pulse sobre la p†gina que
desee mostrar para desplazarse instant†neamente a ella.

:p.El panel de navegaci¢n puede ocultarse y volverse a mostrar de cualquiera de
las siguientes formas&colon.

:ul compact.
:li.:link reftype=hd res=302.Mostrar panel de navegaci¢n (opci¢n del men£ Ventana):elink.
:li.:link reftype=hd res=026.Mostrar/Ocultar panel de navegaci¢n:elink.
:li.:link reftype=hd res=400.Tecla r†pida F9:elink.
:eul.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=200.Men£s:elink.
.br
:link reftype=hd res=008.Panel de contenido:elink.
:edl.

.* ............................................................................
:h3 res=008 name=document_pane
    x=left y=bottom width=100% height=100%.Panel de contenido

El Panel de contenido muestra el archivo seleccionado. El documento (o imagen,
dependiendo del tipo de archivo cargado actualmente) se puede :link reftype=hd
res=030.cambiar de tama§o:elink., :link reftype=hd res=280.girar 90 &deg. en
sentido horario:elink., :link reftype=hd res=281.girar 90 &deg. en sentido
antihorario:elink., :link reftype=hd res=034.aumentar o reducir de
tama§o:elink. o :link reftype=hd res=303.mostrar a pantalla completa:elink. o
:link reftype=hd res=304.en modo presentaci¢n:elink..

:p.El panel de contenido tambiÇn permite mover manualmente la secci¢n mostrada
arrastrando con el segundo bot¢n del rat¢n, lo cual har† cambiar el puntero del
rat¢n a la mano abierta :artwork runin name='hand_closed.bmp'. para arrastrar.

:p.Generalmente los enlaces de un documento aparecen en un color que contrasta
(azul en el caso de los PDFs, pero otros m¢dulos pueden utilizar colores
diferentes) y cuando el cursor del rat¢n flota sobre uno, el puntero cambia a
la mano :artwork runin name='hand.bmp'.&per. Los enlaces pueden llevar a otras
partes del mismo documento, a otros documentos, o pueden abrir programas
externos (p.e. para enviar correo o visitar Internet).

:p.Los documentos soportados pueden verse con Lucide no s¢lo pasando el nombre
de archivo como par†metro de ejecuci¢n o desde el :link reftype=hd
res=102.di†logo Abrir archivo:elink., sino tambiÇn arrastrando sus iconos hasta
el panel de contenido.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=200.Men£s:elink.
.br
:link reftype=hd res=007.Panel de navegaci¢n:elink.
.br
:link reftype=hd res=510.Abrir enlaces:elink.
.br
:link reftype=hd res=740.Enlaces en archivos PDF:elink.
:edl.


.* ............................................................................
:h2 res=020 name=toolbar
x=left y=bottom width=100% height=100%.Barra de herramientas

La barra de herramientas proporciona acceso directo a algunas funciones de
Lucide de uso com£n&colon.

:ul compact.
:li.:link reftype=hd res=022.Bot¢n Abrir documento:elink.
:li.:link reftype=hd res=024.Bot¢n Imprimir:elink.
:li.:link reftype=hd res=026.Bot¢n Mostrar/ocultar panel de navegaci¢n:elink.
:li.:link reftype=hd res=028.Controles de navegaci¢n:elink.
:li.:link reftype=hd res=030.Controles de escala:elink.
:li.:link reftype=hd res=032.Bot¢n de b£squeda:elink.
:li.:link reftype=hd res=034.Bot¢n de aumento:elink.
:eul.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=200.Men£s:elink.
.br
:link reftype=hd res=100.Di†logos y contenedores:elink.
:edl.

.* ............................................................................
:h3 res=022 name=open_document_button
    x=left y=bottom width=100% height=100%.Bot¢n Abrir documento

El bot¢n Abrir documento
:artwork runin name='open.bmp'.
:artlink.
:link reftype=hd res=102.
:eartlink.
de la barra de herramientas invoca el
:link reftype=hd res=102.di†logo Abrir archivo:elink..

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h3 res=024 name=print_button
    x=left y=bottom width=100% height=100%.Imprimir...

El bot¢n Imprimir
:artwork runin name='print.bmp'.
:artlink.
:link reftype=hd res=104.
:eartlink.
de la barra de herramientas invoca el
:link reftype=hd res=104.di†logo Imprimir:elink..

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=224.Imprimir...:elink.
.br
:link reftype=hd res=104.Di†logo Imprimir:elink.
:edl.

.* ............................................................................
:h3 res=026 name=nav_pane_button
    x=left y=bottom width=100% height=100%.Mostrar/Ocultar panel de navegaci¢n

El bot¢n Mostrar/Ocultar panel de navegaci¢n :artwork runin name='navpanel.bmp'.
de la barra de herramientas alterna entre desactivar y reactivar el :link
reftype=hd res=007.panel del navegaci¢n:elink..

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=007.Panel de navegaci¢n:elink.
.br
:link reftype=hd res=400.Teclas r†pidas:elink.
:edl.

.* ............................................................................
:h3 res=028 name=nav_controls_toolbar
    x=left y=bottom width=100% height=100%.Controles de navegaci¢n

Se proporcionan controles de navegaci¢n est†ndar mediante botones pulsables para
acceder a las p†ginas: primera
:artwork runin name='firstpage.bmp'.
:artlink.
:link reftype=hd res=272.
:eartlink.,
£ltima
:artwork runin name='lastpage.bmp'.
:artlink.
:link reftype=hd res=275.
:eartlink.,
anterior
:artwork runin name='prevpage.bmp'.
:artlink.
:link reftype=hd res=273.
:eartlink.
y siguiente
:artwork runin name='nextpage.bmp'.
:artlink.
:link reftype=hd res=274.
:eartlink.,
as° como un campo de entrada en el que introducir un n£mero de p†gina
espec°fico. Adem†s, se pueden utilizar las flechas arriba y abajo para
incrementar o disminuir el n£mero de p†gina actual.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=007.Panel de navegaci¢n:elink.
.br
:link reftype=hd res=272.Primera p†gina:elink.
.br
:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=276.Ir a p†gina...:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h3 res=030 name=scaling_controls_toolbar
    x=left y=bottom width=100% height=100%.Controles de escala

La escala del documento cargado actualmente se puede ajustar mediante tama§os
predeterminados (real
:artwork runin name='100perc.bmp'.
:artlink.
:link reftype=hd res=263.
:eartlink., ajustado a la ventana
:artwork runin name='fitpage.bmp'.
:artlink.
:link reftype=hd res=262.
:eartlink., o ajustado al ancho
:artwork runin name='fitwidth.bmp'.
:artlink.
:link reftype=hd res=264.
:eartlink.) o seleccionado de la lista desplegable uno de estos valores
predeterminados o un factor de escala por porcentaje.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=260.Men£ Ver:elink.
.br
:link reftype=hd res=034.Aumentar/Reducir tama§o:elink.
.br
:link reftype=hd res=263.Tama§o real:elink.
.br
:link reftype=hd res=264.Ajustar al ancho:elink.
.br
:link reftype=hd res=268.Aumentar tama§o:elink.
.br
:link reftype=hd res=269.Reducir tama§o:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h3 res=032 name=find_buttons
    x=left y=bottom width=100% height=100%.Botones de b£squeda

Se puede buscar texto en los documentos soportados mediante el bot¢n Buscar...
:artwork runin name='find.bmp'.
:artlink.
:link reftype=hd res=108.
:eartlink. que a su vez abre el
:link reftype=hd res=108.di†logo Buscar:elink.
y el bot¢n Buscar siguiente
:artwork runin name='findagain.bmp'.
:artlink.
:link reftype=hd res=248.
:eartlink.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=240.Men£ Editar:elink.
.br
:link reftype=hd res=211.Men£ de contexto del documento:elink.
.br
:link reftype=hd res=246.Buscar...:elink.
.br
:link reftype=hd res=108.Di†logo Buscar:elink.
:edl.

.* ............................................................................
:h3 res=034 name=zoom_tool
    x=left y=bottom width=100% height=100%.Bot¢n Aumentar/reducir tama§o

Cambiar el tama§o del contenido de la ventana es tan f†cil como pulsar el bot¢n
Aumentar/reducir tama§o :artwork runin name='mglass.bmp'.&per. Cuando se pulsa,
el bot¢n indica el estado de activaci¢n de la herramienta, y el puntero del
rat¢n se convierte en la lupa :artwork runin name='zoom_in.bmp'.

:p.Para utilizar la herramienta, pulse el bot¢n izquierdo del rat¢n sobre el
contenido para aumentar el tama§o o el derecho para disminuirlo. El factor de
escala del tama§o actual se muestra en la barra de herramientas, en la lista
desplegable Tama§o.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=260.Men£ Ver:elink.
:edl.

.* ............................................................................
:h2 res=100 name=dialogs
    x=left y=bottom width=100% height=100%.Di†logos y contenedores

El resto de operaciones se realizan mediante di†logos y contenedores que ayudan
a guiar al usuario a travÇs de cada proceso y ofrecen opciones adicionales para
cada tarea seleccionada. La ayuda sensible al contexto mostrar† informaci¢n
relevante para cada uno mediante el bot¢n :hp2.Ayuda:ehp2. o pulsando F1.

:ul compact.
:li.:link reftype=hd res=102.Abrir archivo:elink.
:li.:link reftype=hd res=104.Imprimir:elink.
:li.:link reftype=hd res=106.Lista de m¢dulos:elink.
:li.:link reftype=hd res=108.Buscar:elink.
:li.:link reftype=hd res=110.Preferencias:elink.
:li.:link reftype=hd res=112.Ir a la p†gina:elink.
:li.:link reftype=hd res=114.Informaci¢n sobre el documento:elink.
:li.:link reftype=hd res=116.Fuentes del documento:elink.
:li.:link reftype=hd res=118.Archivo protegido:elink.
:li.:link reftype=hd res=120.Progreso:elink.
:eul.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=020.Barra de herramientas:elink.
.br
:link reftype=hd res=100.Men£s:elink.
:edl.

.* ............................................................................
:h3 res=102 name=open_file_dialog
    x=left y=bottom width=100% height=100%.Abrir archivo

El :hp2.di†logo Abrir archivo:ehp2. muestra una selecci¢n de los archivos
disponibles as° como un subpanel de vista en miniatura del archivo seleccionado
actualmente. La lista de archivos puede filtrarse para mostrar todos o s¢lo los
tipos de archivo soportados en el directorio seleccionado.

:p.Adem†s de navegar por unidad y directorio, arriba hay disponible un campo
para el nombre de archivo, en el que introducir lo que se desee manualmente.

:p.Si hay una miniatura del documento disponible (consulte :link reftype=hd
res=512.aqu°:elink. y :link reftype=hd res=110.aqu°:elink. la creaci¢n de
miniaturas), se mostrar† en el panel de vista previa del lado derecho del
di†logo Abrir archivo.

:p.El estado actual de la opci¢n de crear miniaturas se refleja en el estado de
la :hp2.casilla Crear miniatura:ehp2.. Utilizando esta casilla es posible
soslayar la configuraci¢n para el archivo seleccionado.

:nt.La :hp2.casilla Crear miniatura:ehp2. no cambia el estado de la opci¢n
general de crear miniaturas. En su lugar, marcar o desmarcar esta casilla s¢lo
afecta al archivo seleccionado actualmente. Para cambiar el valor por omisi¢n,
dir°jase al :link reftype=hd res=110.di†logo Preferencias:elink..:ent.

:hp2.Ayuda:ehp2. muestra este panel.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=022.Bot¢n Abrir documento:elink.
.br
:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
.br
:link reftype=hd res=217.Èltimo enlace seguido:elink.
.br
:link reftype=hd res=219.Guardar...:elink.
.br
:link reftype=hd res=220.Guardar como...:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
.br
:link reftype=hd res=512.Creaci¢n de miniaturas:elink.
.br
:link reftype=hd res=110.Di†logo Preferencias:elink.
.br
:link reftype=hd res=104.Di†logo Imprimir:elink.
:edl.

.* ............................................................................
:h3 res=104 name=print_dialog
    x=left y=bottom width=100% height=100%.Di†logo Imprimir

El di†logo Imprimir se divide en cinco †reas, con botones de Imprimir y
Cancelar en la parte inferior.

:p.:hp2.Impresora:ehp2.

:p.Este †rea presenta una lista desplegable para seleccionar la impresora de
destino con el controlador asociado que se muestra debajo, y un bot¢n de
Propiedades del trabajo que abre el cuaderno de propiedades del trabajo del
sistema.

:p.:hp2.Rango de impresi¢n y n.ß de copias:ehp2.

:p.Aqu° se puede establecer el rango y †mbito de impresi¢n (todas, p†gina
actual, p†ginas entre valores y pares, impares o ambas), as° como el n£mero de
copias y una opci¢n de orden inverso.

:p.:hp2.Tipo de impresi¢n:ehp2.

:p.La salida nativa de Lucide es PostScript. Adem†s, es posible imprimir como
imagen (Çste es el £nico modo disponible para impresoras no PostScript) y, si
se desea, se puede establecer una calidad de imagen superior para imprimir con
mayor detalle.

:p.TambiÇn hay una casilla para seleccionar la opci¢n de imprimir a archivo
(disponible s¢lo para las impresoras PostScript, puesto que vuelca datos
PostScript sin procesar al archivo). Seleccionar esta opci¢n y pulsar Imprimir
abrir† el di†logo Abrir archivo del sistema para permitir introducir el nombre
del archivo (la extensi¢n .ps deber°a estar preestablecida).

:nt.Seleccionar la opci¢n de mejor calidad de imagen puede tardar
considerablemente m†s en generar los datos de salida y consumir m†s memoria de
impresi¢n y del sistema en el proceso.:ent.

:hp2.Orientaci¢n de las p†ginas:ehp2.

:p.Seleccione orientaci¢n vertical o apaisada para la salida impresa.

:nt.Si se est† estableciendo una orientaci¢n en las Propiedades del trabajo del
propio objeto impresora, en general se recomienda mantener el valor por defecto
de esta opci¢n.:ent.

:hp2.M†rgenes (mm):ehp2.

:p.Use las flechas para ajustar los valores o introduzca a mano las medidas en
mil°metros para los m†rgenes alrededor de la p†gina. La casilla Ignorar los
m†rgenes de la impresora aplicar† las medidas a las dimensiones totales de la
p†gina, mientras que con ella desmarcada los valores seleccionados se a§adir†n
a los m†rgenes que la impresora ya tenga configurados.

:p.El formato seleccionado se muestra al final de este †rea.

:p.Cuando haya establecido todas las opciones, pulse :hp2.Imprimir:ehp2. para
enviar los datos a la impresora (o un archivo, si ha seleccionado Imprimir a
archivo), o pulse :hp2.Cancelar:ehp2. para cerrar el di†logo Imprimir volviendo
a la vista anterior del archivo. :hp2.Ayuda:ehp2. muestra informaci¢n
sensible al contexto.

:p.El di†logo Imprimir no se abrir† si Lucide no encuentra ninguna impresora.
En su lugar se mostrar† un mensaje de error.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=024.Bot¢n Imprimir:elink.
.br
:link reftype=hd res=224.Imprimir...:elink.
.br
:link reftype=hd res=514.Controlar la salida de impresi¢n:elink.
:edl.

.* ............................................................................
:h3 res=106 name=plugins_box
    x=left y=bottom width=100% height=100%.Lista de m¢dulos

La Lista de m¢dulos muestra una vista tabulada de los m¢dulos cargados, una
breve descripci¢n y una lista de las extensiones de nombre de archivo
soportadas por cada uno. La lista no puede modificarse.

:nt.Si un m¢dulo no aparece en esta lista, bien no est† instalado o bien
:hp2.Lucide:ehp2. no pudo cargarlo.:ent.

:hp2.Ayuda:ehp2. muestra este panel.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=226.Lista de m¢dulos...:elink.
.br
:link reftype=hd res=114.Contenedor Informaci¢n sobre el documento:elink.
.br
:link reftype=hd res=116.Contenedor Fuentes del documento:elink.
.br
:link reftype=hd res=830.M¢dulos incluidos:elink.
:edl.

.* ............................................................................
:h3 res=108 name=find_dialog
    x=left y=bottom width=100% height=100%.Di†logo Buscar

Si el documento contiene texto, se puede buscar en el contenido mediante el
di†logo Buscar. Introduzca una cadena de texto que buscar y seleccione las
opciones apropiadas para coincidencias de may£sculas y min£sculas y/o b£squeda
hacia atr†s en el documento y pulse :hp2.Bien:ehp2. para comenzar la b£squeda o
:hp2.Cancelar:ehp2. para cerrar el di†logo sin buscar. :hp2.Ayuda:ehp2. muestra
este mismo panel.

:p.Durante la b£squeda, se muestra un di†logo de progreso y adem†s un mensaje
si no se encuentran resultados.

:p.Al terminar la b£squeda, los tÇrminos encontrados en el documento se
presentar†n resaltados.

:nt.
Actualmente no es posible buscar en PDFs u otros archivos que s¢lo
contengan im†genes y no texto como tal. Para determinar si Çste es el tipo de
documento que est† viendo, intente seleccionar texto con el primer bot¢n del
rat¢n. Si se selecciona correctamente, la funci¢n de b£squeda tambiÇn deber°a
funcionar como es esperable.

:p.Puede buscar cadenas de texto de hasta 100 caracteres. El campo de entrada
no admite introducir manualmente ni pegar un texto m†s largo.
:ent.

:p.:hp2.Ayuda:ehp2. muestra este mismo panel.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=246.Buscar...:elink.
.br
:link reftype=hd res=248.Buscar siguiente:elink.
.br
:link reftype=hd res=032.Botones de b£squeda:elink.
.br
:link reftype=hd res=242.Copiar:elink.
.br
:link reftype=hd res=244.Seleccionar todo:elink.
:edl.

.* ............................................................................
:h3 res=110 name=settings_dialog
    x=left y=bottom width=100% height=100%.Di†logo Preferencias

El di†logo Preferencias permite configurar los valores por omisi¢n (para todos
los documentos) de mostrar las p†ginas de una en una o en estilo continuo, el
tama§o (nivel de escala) o de creaci¢n de miniaturas. Los valores de
presentaci¢n se pueden cambiar mediante los men£s de la aplicaci¢n o la barra
de herramientas, pero s¢lo para la sesi¢n actual. Por tanto, los documentos que
se abran en la misma ventana de :hp2.Lucide:ehp2. lo har†n con estos nuevos
valores, pero los que se abran en otras ventanas lo har†n con los valores por
omisi¢n establecidos.

:p.Pulsar :hp2.Bien:ehp2. guarda los valores que muestre el di†logo, mientras
que :hp2.Cancelar:ehp2. mantiene intactos los previos. :hp2.Ayuda:ehp2. muestra
este panel.

:p.:hp2.Acerca de las miniaturas:ehp2.

:p.El valor de creaci¢n de miniaturas se puede obviar para archivos en
particular en el momento de abrir un nuevo archivo (des)marcando la casilla
ÆCrear miniaturaØ (n¢tese el singular) en el :link reftype=hd res=102.di†logo
Abrir archivo:elink..

:p.Para que la miniatura se guarde en disco, el archivo debe residir en un
medio escribible, con los permisos de acceso necesarios para modificar archivos
all°, y el sistema de archivos debe soportar atributos extendidos.

:note text='Nota 1:'.Como precauci¢n de seguridad, :hp3.nunca:ehp3. se crean
miniaturas de archivos PDF protegidos.

:note text='Nota 2:'.Las miniaturas se guardan en atributos extendidos,
conectados al archivo original. Crear una miniatura no altera el contenido del
archivo original de forma alguna, aunque la copia posterior de un archivo con
vista en miniatura a un volumen que no soporte atributos extendidos har† que
aquÇlla se pierda al no poder copiarse normalmente. Lo mismo ocurrir† al
transmitir el archivo a travÇs de Internet por FTP o adjunto a un mensaje de
correo, (a no ser que se incluya en un archivo zip u otro formato de
archivador): la miniatura no se enviar† con el archivo. El archivo original y
la miniatura, si se gener¢ una, no se ver†n alterados por estas operaciones, no
obstante.


:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=284.Ver una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=030.Controles de escala:elink.
.br
:link reftype=hd res=512.Creaci¢n de miniaturas:elink.
:edl.

.* ............................................................................
:h3 res=112 name=go_to_page_dialog
    x=left y=bottom width=100% height=100%.Di†logo Ir a p†gina

El di†logo ÆIr a la p†gina...Ø permite introducir el n£mero de p†gina deseado
para poder navegar r†pidamente. Introduzca el n£mero de p†gina en el campo de
entrada y pulse :hp2.Bien:ehp2. para comenzar la b£squeda o
:hp2.Cancelar:ehp2.. :hp2.Ayuda:ehp2. muestra este panel.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=272.Primera p†gina:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=028.Controles de navegaci¢n:elink.
:edl.

.* ............................................................................
:h3 res=114 name=document_info_box
    x=left y=bottom width=100% height=100%.Informaci¢n del documento

El contenedor Informaci¢n del documento ofrece una lista de detalles que
describen el archivo actual. El tipo de informaci¢n mostrada depende del tipo
de archivo, as° como de quÇ se us¢ para crearlo (no todos los programas ofrecen
todos los detalles).

:p.Aunque el contenido es de s¢lo lectura, es posible seleccionar una o m†s
l°neas con el rat¢n utilizando los modificadores est†ndar de OS/2, tales como
:hp2.Ctrl+/:ehp2. para seleccionar todo, :hp2.Ctrl+BR1:ehp2. para seleccionar
l°neas independientes o :hp2.May£s+BR2:ehp2. para seleccionar un intervalo, y
copiar el contenido de la selecci¢n al portapapeles o †rea com£n utilizando
:hp2.Ctrl+Ins:ehp2. o :hp2.Ctrl+C:ehp2..

:p.:hp2.Cerrar:ehp2. descarta este di†logo y :hp2.Ayuda:ehp2. muestra este
panel.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=106.Lista de m¢dulos:elink.
.br
:link reftype=hd res=226.Lista de m¢dulos...:elink.
.br
:link reftype=hd res=116.Fuentes del documento:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=800.Enfoque:elink.
:edl.

.* ............................................................................
:h3 res=116 name=fonts_info_box
    x=left y=bottom width=100% height=100%.Fuentes del documento

El contenedor Fuentes del documento ofrece una vista tabular de todas las
fuentes utilizadas en el documento, su tipo, si han sido incluidas en el
documento o sustituidas y quÇ fuente se utiliza en su lugar.

:p.Aunque el contenido es de s¢lo lectura, es posible seleccionar una o m†s
l°neas con el rat¢n utilizando los modificadores est†ndar de OS/2, tales como
:hp2.Ctrl+/:ehp2. para seleccionar todo, :hp2.Ctrl+BR1:ehp2. para seleccionar
l°neas independientes o :hp2.May£s+BR2:ehp2. para seleccionar un intervalo, y
copiar el contenido de la selecci¢n al portapapeles o †rea com£n utilizando
:hp2.Ctrl+Ins:ehp2. o :hp2.Ctrl+C:ehp2..

:p.:hp2.Cerrar:ehp2. descarta este di†logo y :hp2.Ayuda:ehp2. muestra este
panel.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=106.Lista de m¢dulos:elink.
.br
:link reftype=hd res=226.Lista de m¢dulos...:elink.
.br
:link reftype=hd res=114.Informaci¢n del documento:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=800.Enfoque:elink.
:edl.

.* ............................................................................
:h3 res=118 name=password_dialog
    x=left y=bottom width=100% height=100%.Archivo protegido

Si el documento que quiere abrir est† cifrado, se le presentar† el di†logo
Archivo protegido. Introduzca la contrase§a en el campo de entrada y pulse
:hp2.Bien:ehp2. para intentar abrirlo o :hp2.Cancelar:ehp2. para abortar.
:hp2.Ayuda:ehp2. muestra este panel.

:p.Los posibles motivos por los que puede fallar la apertura en estos casos
incluyen:

:note text='Contrase§a incorrecta:'.En este caso, :hp2.Lucide:ehp2. mostrar†
este di†logo de forma continua hasta que se introduzca la contrase§a correcta o
se pulsen Esc o el bot¢n :hp2.Cancelar:ehp2.. Una vez que se vuelva al
Panel de contenido (en blanco), se puede seleccionar otro archivo para abrir.

:note text='Tipo de cifrado no soportado:'.:hp2.Lucide:ehp2. no distingue entre
documentos protegidos con contrase§a y otros mÇtodos de seguridad que no puede
descifrar actualmente. De igual forma, puede que se le presente el di†logo
Archivo protegido para documentos cifrados utilizando un certificado, en los
que no se admitir† una contrase§a. :hp2.Lucide:ehp2. no tiene forma de abrir
estos archivos.

:note text='Cancelar'.Pulsar el bot¢n :hp2.Cancelar:ehp2. o Esc cerrar† este
di†logo devolviÇndole a un panel de contenido vac°o.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=102.Di†logo Abrir archivo:elink.
.br
:link reftype=hd res=730.Seguridad PDF:elink.
.br
:link reftype=hd res=840.Seguridad:elink.
:edl.

.* ............................................................................
:h3 res=120 name=progress_dialog
    x=left y=bottom width=100% height=100%.Di†logo Progreso

El di†logo Progreso se presenta para cualquier operaci¢n no instant†nea. En
algunos casos, puede mostrarse con el bot¢n :hp2.Cancelar:ehp2. para poder
anular la operaci¢n.

.* ............................................................................
:h2 res=200 name=menu
    x=left y=bottom width=100% height=100%.Men£

El men£ principal ofrece las siguientes funciones y submen£s&colon.

:ul compact.
:li.:link reftype=hd res=210.Men£ Documento:elink.
:li.:link reftype=hd res=211.Men£ de contexto del documento:elink.
:li.:link reftype=hd res=240.Men£ Editar:elink.
:li.:link reftype=hd res=260.Men£ Ver:elink.
:li.:link reftype=hd res=300.Men£ Ventana:elink.
:li.:link reftype=hd res=360.Menu Ayuda:elink.
:eul.

.* ............................................................................
:h3 res=210 name=document_menu
    x=left y=bottom width=100% height=100%.Men£ Documento

El men£ Documento contiene las siguientes entradas:

:ul compact.
:li.:link reftype=hd res=212.Nueva ventana:elink.
:li.:link reftype=hd res=214.Abrir...:elink.
:li.:link reftype=hd res=216.Siguiente/Anterior:elink.
:li.:link reftype=hd res=218.Archivos recientes:elink.
:li.:link reftype=hd res=217.Èltimo enlace seguido:elink.
:li.:link reftype=hd res=219.Guardar...:elink.
:li.:link reftype=hd res=220.Guardar como...:elink.
:li.:link reftype=hd res=222.Cerrar:elink.
:li.:link reftype=hd res=224.Imprimir...:elink.
:li.:link reftype=hd res=226.Lista de m¢dulos...:elink.
:li.:link reftype=hd res=228.Salir:elink.
:eul.

.* ............................................................................
:h4 res=212 name=new_window
    x=left y=bottom width=100% height=100%.Nueva ventana

Crea una nueva ventana de :hp2.Lucide:ehp2. con una configuraci¢n similar a la
actual. Las diversas ventanas operan independientemente, lo que hace posible
abrir distintos documentos (y de distinto tipo) desde diferentes ubicaciones y
a distintos tama§os.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h4 res=214 name=open
    x=left y=bottom width=100% height=100%.Abrir...

Abre el :link reftype=hd res=102.di†logo Abrir archivo:elink. en la ventana
actual y a continuaci¢n carga el archivo seleccionado utilizando las opciones
de vista actuales.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=212.Nueva ventana:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h4 res=216 name=next_previous
    x=left y=bottom width=100% height=100%.Siguiente/Anterior

Abre el siguiente archivo (o el anterior) de cualquier tipo soportado del
directorio actual, sustituyendo al que se muestra actualmente.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=212.Nueva ventana:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h4 res=218 name=recent_files
    x=left y=bottom width=100% height=100%.Archivos recientes

La lista Archivos recientes permite seleccionar r†pidamente un archivo de entre
los nueve que se hayan abierto m†s recientemente. TambiÇn ofrece una opci¢n de
vaciar la lista en s°.

:p.El archivo seleccionado sustituir† al que se muestra actualmente.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=212.Nueva ventana:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h4 res=217 name=Last_link_origin
    x=left y=bottom width=100% height=100%.Èltimo enlace seguido

Esta entrada del men£ s¢lo se habilita si se ha desplazado por el documento
seleccionando al menos un enlace interno. Al seleccionarla, le devolver† al
punto del documento donde se encuentre el enlace.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=276.Ir a la p†gina...:elink.
:edl.

.* ............................................................................
:h4 res=219 name=save
    x=left y=bottom width=100% height=100%.Guardar...

Esta entrada del men£ guarda el archivo actual. S¢lo est† disponible para
formularios PDF cumplimentables. Si es necesario conservar el formulario original
(en blanco), utilice :link reftype=hd res=220.Guardar como...:elink..

:p.En realidad, este men£ guarda el documento en un archivo temporal, que se
carga y se guarda en el archivo original, que vuelve a cargarse y entonces borra
el archivo temporal.

:p.Parte de las recargas puede resultar visible en pantalla. Si falla una
operaci¢n de guardar, el archivo temporal puede permanecer en el directorio
%TEMP%. êsta es una limitaci¢n de Poppler, que s¢lo permite guardar un archivo
con otro nombre.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h4 res=220 name=save_as
    x=left y=bottom width=100% height=100%.Guardar como...

Abre el di†logo de selecci¢n de archivos est†ndar del sistema para permitir
guardar el archivo actual con un nombre diferente. A menudo se usa para
cumplimentar formularios PDF cuando hay que conservar el original.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=219.Guardar...:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h4 res=222 name=close
    x=left y=bottom width=100% height=100%.Cerrar

Cierra el archivo actual, dejando la ventana en su configuraci¢n actual. Desde
aqu° se puede abrir un nuevo archivo de las formas habituales.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=212.Nueva ventana:elink.
.br
:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
:edl.

.* ............................................................................
:h4 res=224 name=print
    x=left y=bottom width=100% height=100%.Imprimir...

Abre el :link reftype=hd res=104.di†logo Imprimir:elink., donde se pueden
establecer las opciones del trabajo de impresi¢n antes de enviar el archivo a
la impresora seleccionada.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=104.Di†logo Imprimir:elink.
:edl.

.* ............................................................................
:h4 res=226 name=plugins_list
    x=left y=bottom width=100% height=100%.Lista de m¢dulos...

Abre la :link reftype=hd res=106.Lista de m¢dulos:elink., que muestra una vista
tabular de cada m¢dulo cargado, una breve descripci¢n y una lista de las
extensiones de archivo soportadas que maneja. La lista es de s¢lo lectura.

:nt.Si un m¢dulo no aparece en esta lista, no est† instalado o bien
:hp2.Lucide:ehp2. no ha podido cargarlo.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=106.Lista de m¢dulos:elink.
.br
:link reftype=hd res=116.Fuentes del documento:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=830.M¢dulos incluidos:elink.
:edl.

.* ............................................................................
:h4 res=228 name=exit
    x=left y=bottom width=100% height=100%.Salir

Sale del programa, cerrando completamente la ventana actual de
:hp2.Lucide:ehp2., aunque cualesquiera otras instancias contin£an en ejecuci¢n.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=212.Nueva ventana:elink.
.br
:link reftype=hd res=214.Abrir...:elink.
.br
:link reftype=hd res=216.Siguiente/Anterior:elink.
.br
:link reftype=hd res=218.Archivos recientes:elink.
.br
:link reftype=hd res=222.Cerrar:elink.
:edl.

.* ............................................................................
:h3 res=211 name=document_context_menu
    x=left y=bottom width=100% height=100%.Men£ de contexto del documento

Pulse el segundo bot¢n del rat¢n con el cursor sobre el panel de contenido para
abrir este men£.

:p.El men£ de contexto del documento tiene las siguientes entradas:

:ul compact.
:li.:link reftype=hd res=217.Èltimo enlace seguido:elink.
:li.:link reftype=hd res=242.Copiar:elink.
:li.:link reftype=hd res=244.Seleccionar todo:elink.
:li.:link reftype=hd res=246.Buscar...:elink.
:li.:link reftype=hd res=248.Buscar siguiente:elink.
:li.:link reftype=hd res=224.Imprimir...:elink.
:eul.

.* ............................................................................
:h3 res=240 name=edit_menu
    x=left y=bottom width=100% height=100%.Men£ Editar

El men£ Editar tiene las siguientes entradas:

:ul compact.
:li.:link reftype=hd res=242.Copiar:elink.
:li.:link reftype=hd res=244.Seleccionar todo:elink.
:li.:link reftype=hd res=246.Buscar...:elink.
:li.:link reftype=hd res=248.Buscar siguiente:elink.
:li.:link reftype=hd res=250.Preferencias:elink.
:li.:link reftype=hd res=228.Salir:elink.
:eul.

.* ............................................................................
:h4 res=242 name=copy
    x=left y=bottom width=100% height=100%.Copiar

Copia la selecci¢n actual al portapapeles o †rea com£n del sistema, con las
limitaciones de tama§o del propio portapapeles.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=420.Uso del rat¢n:elink.
.br
:link reftype=hd res=502.Seleccionar contenido:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h4 res=244 name=select_all
    x=left y=bottom width=100% height=100%.Seleccionar todo

Selecciona la vista actual del doumento al completo.

:nt.Puede ser imposible copiar todo el contenido seleccionado al portapapeles
del sistema debido a limitaciones de tama§o de esta †rea com£n.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=242.Copiar:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=420.Uso del rat¢n:elink.
.br
:link reftype=hd res=502.Seleccionar contenido:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h4 res=246 name=find
    x=left y=bottom width=100% height=100%.Buscar

Abre el :link reftype=hd res=108.di†logo Buscar:elink., que muestra un campo de
entrada en el que introducir texto para buscar.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=032.Herramienta de b£squeda:elink.
.br
:link reftype=hd res=108.Di†logo Buscar:elink.
.br
:link reftype=hd res=504.Buscar texto:elink.
.br
:link reftype=hd res=242.Copiar:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=502.Seleccionar contenido:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h4 res=248 name=find_again
    x=left y=bottom width=100% height=100%.Buscar siguiente

Repite la b£squeda utilizando el criterio de b£squeda actual, parando en el
siguiente bloque de texto resaltado.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=032.Herramienta de b£squeda:elink.
.br
:link reftype=hd res=108.Di†logo Buscar:elink.
.br
:link reftype=hd res=504.Buscar texto:elink.
.br
:link reftype=hd res=242.Copiar:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=502.Seleccionar contenido:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h4 res=250 name=settings
    x=left y=bottom width=100% height=100%.Preferencias

Abre el :link reftype=hd res=110.di†logo Preferencias:elink., que permite
configurar los valores por omisi¢n (para todos los documentos) de mostrar las
p†ginas de una en una o en estilo continuo y el tama§o (nivel de escala).

:nt.Los valores de presentaci¢n se pueden cambiar mediante los men£s de la
aplicaci¢n o la barra de herramientas, pero s¢lo para la sesi¢n actual. Por
tanto, los documentos que se abran en la misma ventana de :hp2.Lucide:ehp2. lo
har†n con estos nuevos valores, pero los que se abran en otras ventanas lo
har†n con los valores por omisi¢n establecidos.:ent.


:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=030.Controles de escala:elink.
:edl.

.* ............................................................................
:h3 res=260 name=view_menu
x=left y=bottom width=100% height=100%.Men£ Ver

El men£ Ver tiene las siguientes entradas:

:ul compact.
:li.:link reftype=hd res=262.Ajustar a la ventana:elink.
:li.:link reftype=hd res=263.Tama§o real:elink.
:li.:link reftype=hd res=264.Ajustar al ancho:elink.
:li.:link reftype=hd res=268.Aumentar tama§o:elink.
:li.:link reftype=hd res=269.Disminuir tama§o:elink.
:li.:link reftype=hd res=272.Primera p†gina:elink.
:li.:link reftype=hd res=273.P†gina anterior:elink.
:li.:link reftype=hd res=274.P†gina siguiente:elink.
:li.:link reftype=hd res=275.Èltima p†gina:elink.
:li.:link reftype=hd res=276.Ir a la p†gina...:elink.
:li.:link reftype=hd res=280.Rotar 90&deg. en sentido horario:elink.
:li.:link reftype=hd res=281.Rotar 90&deg. en sentido antihorario:elink.
:li.:link reftype=hd res=284.Una p†gina cada vez:elink.
:li.:link reftype=hd res=285.Estilo continuo:elink.
:li.:link reftype=hd res=290.Informaci¢n sobre el documento...:elink.
:li.:link reftype=hd res=291.Fuentes utilizadas...:elink.
:eul.

.* ............................................................................
:h4 res=262 name=fit_in_window
    x=left y=bottom width=100% height=100%.Ajustar a la ventana

Establece el :link reftype=hd res=034.tama§o:elink. (escala) actual de
forma que en el :link reftype=hd res=008.panel de contenido:elink. quepa una
p†gina del documento completa (independientemente de la opci¢n de presentaci¢n
:link reftype=hd res=284.Ver una p†gina cada vez:elink. / :link reftype=hd
res=285.Estilo continuo:elink.). Redimensionar el panel de contenido mediante el
rat¢n, los controles est†ndar de la ventana o las opciones del :link reftype=hd
res=300.men£ Ventana:elink. har† que la vista se reescale proporcionalmente.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=030.Controles de escala:elink.
.br
:link reftype=hd res=034.Tama§o:elink.
.br
:link reftype=hd res=263.Tama§o real:elink.
.br
:link reftype=hd res=264.Ajustar al ancho:elink.
.br
:link reftype=hd res=268.Aumentar tama§o:elink.
.br
:link reftype=hd res=269.Disminuir tama§o:elink.
.br
:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=263 name=actual_size
x=left y=bottom width=100% height=100%.Tama§o real

Establece el :link reftype=hd res=034.tama§o:elink. (escala) actual de tal
forma que en el :link reftype=hd res=008.panel de contenido:elink. se muestre
una sola p†gina (independientemente de la opci¢n de presentaci¢n :link
reftype=hd res=284.Ver una p†gina cada vez:elink. / :link reftype=hd
res=285.Estilo continuo:elink.) a su tama§o original. Redimensionar el panel de
contenido mediante el rat¢n, los controles est†ndar de la ventana o las
opciones del :link reftype=hd res=300.men£ Ventana:elink. har† que aumente o
disminuya el †rea alrededor de la p†gina mostrada (el tama§o relativo de la
p†gina no cambiar†).

:nt.En :link reftype=hd res=304.modo presentaci¢n:elink., la escala volver† al
nivel necesario para presentar una sola p†gina en la resoluci¢n de pantalla
actual.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=030.Controles de escala:elink.
.br
:link reftype=hd res=034.Tama§o:elink.
.br
:link reftype=hd res=262.Ajustar a la ventana:elink.
.br
:link reftype=hd res=264.Ajustar al ancho:elink.
.br
:link reftype=hd res=268.Aumentar tama§o:elink.
.br
:link reftype=hd res=269.Disminuir tama§o:elink.
.br
:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=264 name=fit_width
    x=left y=bottom width=100% height=100%.Ajustar al ancho

Establece el :link reftype=hd res=034.tama§o:elink. (escala) actual de
forma que en el l°mite del ancho del :link reftype=hd res=008.panel de
contenido:elink. quepa una p†gina (independientemente de la opci¢n de
presentaci¢n :link reftype=hd res=284.Ver una p†gina cada vez:elink. / :link
reftype=hd res=285.Estilo continuo:elink.). Puede presentarse una barra de
desplazamiento vertical si la longitud de la vista actual sobrepasa el espacio
vertical disponible en el Panel de contenido. Redimensionar el Panel de
contenido mediante el rat¢n, los controles est†ndar de la ventana o las
opciones del :link reftype=hd res=300.men£ Ventana:elink. har† que la vista se
reescale proporcionalmente.

:nt.En :link reftype=hd res=304.modo presentaci¢n:elink., la escala volver† al
nivel necesario para presentar una sola p†gina en la resoluci¢n de pantalla
actual.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=030.Controles de escala:elink.
.br
:link reftype=hd res=034.Tama§o:elink.
.br
:link reftype=hd res=263.Tama§o real:elink.
.br
:link reftype=hd res=262.Ajustar al alto de la ventana:elink.
.br
:link reftype=hd res=268.Aumentar tama§o:elink.
.br
:link reftype=hd res=269.Disminuir tama§o:elink.
.br
:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=268 name=zoom_in
    x=left y=bottom width=100% height=100%.Aumentar el tama§o

Aumentar el tama§o desde el men£ hace que la vista actual en el :link
reftype=hd res=008.Panel de contenido:elink. pase al siguiente :link reftype=hd
res=034.tama§o:elink. (nivel de escala) preestablecido de tal forma que en el
:link reftype=hd res=008.panel de contenido:elink. se muestre una sola p†gina
(independientemente de la opci¢n de presentaci¢n :link reftype=hd res=284.Ver
una p†gina cada vez:elink. / :link reftype=hd res=285.Estilo continuo:elink.).
Redimensionar el panel de contenido mediante el rat¢n, los controles est†ndar
de la ventana o las opciones del :link reftype=hd res=300.men£ Ventana:elink.
har† que aumente o disminuya el †rea alrededor de la p†gina mostrada (el tama§o
relativo de la p†gina no cambiar†). Pueden presentarse barras de desplazamiento
vertical y/ u horizontal si las dimensiones de la vista actual exceden el
tama§o del Panel de contenido.

:nt.En :link reftype=hd res=304.modo presentaci¢n:elink., la escala volver† al
nivel necesario para presentar una sola p†gina en la resoluci¢n de pantalla
actual. Es posible aumentar y reducir el tama§o utilizando las :link reftype=hd
res=400.teclas Ctrl++/Ctrl+-:elink. (aunque no se mostrar† el nuevo factor de
escala).:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=030.Controles de escala:elink.
.br
:link reftype=hd res=034.Tama§o:elink.
.br
:link reftype=hd res=263.Tama§o real:elink.
.br
:link reftype=hd res=264.Ajustar al ancho:elink.
.br
:link reftype=hd res=269.Disminuir tama§o:elink.
.br
:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=269 name=zoom_out
    x=left y=bottom width=100% height=100%.Disminuir el tama§o

Disminuir el tama§o desde el men£ hace que la vista actual en el :link
reftype=hd res=008.Panel de contenido:elink. pase al :link reftype=hd
res=034.tama§o:elink. (nivel de escala) preestablecido inmediatamente inferior
de tal forma que en el :link reftype=hd res=008.panel de contenido:elink. se
muestren tantas p†ginas como quepan verticalmente (independientemente de la
opci¢n de presentaci¢n :link reftype=hd res=284.Ver una p†gina cada vez:elink.
/ :link reftype=hd res=285.Estilo continuo:elink.). Redimensionar el panel de
contenido mediante el rat¢n, los controles est†ndar de la ventana o las
opciones del :link reftype=hd res=300.men£ Ventana:elink. har† que aumente o
disminuya el †rea alrededor de la(s) p†gina(s) mostrada(s) y se muestren m†s o
menos de ellas (el tama§o de p†gina relativo no cambiar†).

:nt.En :link reftype=hd res=304.modo presentaci¢n:elink., la escala volver† al
nivel necesario para presentar una sola p†gina en la resoluci¢n de pantalla
actual.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=030.Controles de escala:elink.
.br
:link reftype=hd res=034.Tama§o:elink.
.br
:link reftype=hd res=263.Tama§o real:elink.
.br
:link reftype=hd res=264.Ajustar al ancho:elink.
.br
:link reftype=hd res=268.Aumentar tama§o:elink.
.br
:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=272 name=first_page
    x=left y=bottom width=100% height=100%.Primera p†gina

Lleva la vista actual hasta el principio del documento.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=276.Ir a la p†gina...:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=273 name=previous_page
    x=left y=bottom width=100% height=100%.P†gina anterior

Lleva la vista actual hasta la p†gina anterior del documento.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=272.Primera p†gina:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=276.Ir a la p†gina...:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=274 name=next_page
    x=left y=bottom width=100% height=100%.P†gina siguiente

Lleva la vista actual hasta la siguiente p†gina del documento.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=272.Primera p†gina:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=276.Ir a la p†gina...:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=275 name=last_page
    x=left y=bottom width=100% height=100%.Èltima p†gina

Lleva la vista actual hasta la £ltima p†gina del documento.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=272.Primera p†gina:elink.
.br
:link reftype=hd res=276.Ir a la p†gina...:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=276 name=go_to_page
    x=left y=bottom width=100% height=100%.Ir a la p†gina...

Abre el :link reftype=hd res=112.di†logo Ir a la p†gina:elink., que permite
navegar r†pidamente a la p†gina que se desee.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=028.Controles de navegaci¢n:elink.
.br
:link reftype=hd res=007.Panel de navegaci¢n:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=280 name=rotate_cw
    x=left y=bottom width=100% height=100%.Rotar 90&deg. en sentido horario

Reorienta la vista actual gir†ndola hacia la derecha hasta ponerla de lado.

:nt.En :link reftype=hd res=304.modo presentaci¢n:elink., la escala volver† al
nivel necesario para presentar una sola p†gina en la resoluci¢n de pantalla
actual, conservando esta nueva orientaci¢n.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=281.Rotar 90&deg. en sentido antihorario:elink.
.br
:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=281 name=rotate_ccw
    x=left y=bottom width=100% height=100%.Rotar 90&deg. en sentido antihorario

Reorienta la vista actual gir†ndola hacia la izquierda hasta ponerla de lado.

:nt.En :link reftype=hd res=304.modo presentaci¢n:elink., la escala volver† al
nivel necesario para presentar una sola p†gina en la resoluci¢n de pantalla
actual, conservando esta nueva orientaci¢n.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=280.Rotar 90&deg. en sentido horario:elink.
.br
:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=284 name=single_page
    x=left y=bottom width=100% height=100%.Una p†gina cada vez

Muestra una p†gina por vez del documento seleccionado, con las proporciones
indicadas en el mismo documente. La barra de desplazamiento vertical se
refiere a la £nica p†gina mostrada, siendo necesario actuar con el teclado, el
men£ o el Panel de navegaci¢n para desplazarse al resto del documento.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=285.Estilo continuo:elink.
.br
:link reftype=hd res=272.Primera p†gina:elink.
.br
:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=276.Ir a la p†gina...:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=420.Uso del rat¢n:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=285 name=continuous
    x=left y=bottom width=100% height=100%.Estilo continuo

Muestra el documento en modo multip†gina, con las p†ginas delimitadas pero con
la capacidad de ser desplazado con suavidad arrastrando los l°mites entre ellas.
La barra de desplazamiento vertical refleja la posici¢n actual en la totalidad
del documento, lo que permite utilizarla junto al rat¢n, el teclado, los men£s
y el Panel de navegaci¢n para moverse desde la posici¢n actual al resto del
documento.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=284.Una p†gina cada vez:elink.
.br
:link reftype=hd res=272.Primera p†gina:elink.
.br
:link reftype=hd res=273.P†gina anterior:elink.
.br
:link reftype=hd res=274.P†gina siguiente:elink.
.br
:link reftype=hd res=275.Èltima p†gina:elink.
.br
:link reftype=hd res=276.Ir a la p†gina...:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=420.Uso del rat¢n:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=290 name=document_info
    x=left y=bottom width=100% height=100%.Informaci¢n sobre el documento...

Abre el :link reftype=hd res=114.contenedor Informaci¢n sobre el
documento:elink., que proporciona detalles sobre el documento abierto
actualmente.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=106.Lista de m¢dulos:elink.
.br
:link reftype=hd res=226.Lista de m¢dulos...:elink.
.br
:link reftype=hd res=291.Fuentes utilizadas...:elink.
.br
:link reftype=hd res=116.Contenedor Fuentes del documento:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=800.Enfoque:elink.
:edl.

.* ............................................................................
:h4 res=291 name=fonts_info
    x=left y=bottom width=100% height=100%.Fuentes utilizadas...

Muestra el :link reftype=hd res=116.contenedor Fuentes del documento:elink.,
que proporciona detalles sobre las fuentes utilizadas (y sustituidas) en el
archivo abierto actualmente.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=106.Lista de m¢dulos:elink.
.br
:link reftype=hd res=226.Lista de m¢dulos...:elink.
.br
:link reftype=hd res=290.Informaci¢n sobre el documento...:elink.
.br
:link reftype=hd res=114.Informaci¢n sobre el documento:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=800.Enfoque:elink.
:edl.

.* ............................................................................
:h3 res=300 name=window_menu
    x=left y=bottom width=100% height=100%.Men£ Ventana

El men£ Ventana contiene las siguientes entradas:

:ul compact.
:li.:link reftype=hd res=302.Mostrar panel de navegaci¢n:elink.
:li.:link reftype=hd res=303.Pantalla completa:elink.
:li.:link reftype=hd res=304.Presentaci¢n:elink.
:eul.

.* ............................................................................
:h4 res=302 name=show_nav_pane
    x=left y=bottom width=100% height=100%.Panel de navegaci¢n

Como el bot¢n :link reftype=hd res=026.Mostrar/ocultar panel de
navegaci¢n:elink. de la barra de herramientas y la :link reftype=hd
res=400.tecla F9:elink., esta opci¢n del men£ alterna entre mostrar y no el
:link reftype=hd res=007.panel de navegaci¢n:elink..

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=007.Panel de navegaci¢n:elink.
.br
:link reftype=hd res=026.Mostrar/ocultar panel de navegaci¢n:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=028.Controles de navegaci¢n:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=303 name=full_screen
    x=left y=bottom width=100% height=100%.Pantalla completa

Extiende la vista hasta llenar por completo la pantalla, retirando la barra de
t°tulo y los bordes de la ventana. El men£ se desplaza hasta el borde superior
de la pantalla. La barra de herramientas contin£a en posici¢n y si est†
activado, el :link reftype=hd res=007.panel de navegaci¢n:elink. contin£a
visible. Todas :link reftype=hd res=400.las teclas de funci¢n:elink. tambiÇn
contin£an activas. Esta vista tambiÇn se puede seleccionar mediante la :link
reftype=hd res=400.tecla F11:elink..

:nt.En este modo es posible hacer flotar otras ventanas por encima de
:hp2.Lucide:ehp2..:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=304.Presentaci¢n:elink.
.br
:link reftype=hd res=026.Mostrar/ocultar panel de navegaci¢n:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=028.Controles de navegaci¢n:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h4 res=304 name=presentation
    x=left y=bottom width=100% height=100%.Presentaci¢n

Extiende la vista hasta llenar por completo la pantalla, retirando la barra de
t°tulo, los bordes de la ventana, el :link reftype=hd res=007.panel de
navegaci¢n:elink. si est† activo, las barras de desplazamiento y el men£.
Algunas :link reftype=hd res=400.teclas de funci¢n:elink. se desactivan. Esta
vista tambiÇn se puede seleccionar mediante la :link reftype=hd res=400.tecla
F5:elink..

:p.Se puede controlar remotamente :hp2.Lucide:ehp2. mediante la interfaz de
canales (PIPE) mencionada en la secci¢n :link reftype=hd res=440.Funciones de
control remoto:elink., utilizada m†s a menudo en este modo.

:note text='Nota 1:'.En este modo es posible hacer flotar otras ventanas por
encima de :hp2.Lucide:ehp2..

:note text='Nota 2:'.En :link reftype=hd res=304.modo presentaci¢n:elink., la
escala volver† al nivel necesario para presentar una sola p†gina en la
resoluci¢n de pantalla actual. Es posible aumentar y reducir el tama§o
utilizando las :link reftype=hd res=400.teclas Ctrl++/Ctrl+-:elink. (aunque no
se mostrar† el nuevo factor de escala).

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=303.Pantalla completa:elink.
.br
:link reftype=hd res=026.Mostrar/ocultar panel de navegaci¢n:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=028.Controles de navegaci¢n:elink.
.br
:link reftype=hd res=440.Funciones de control remoto:elink.
:edl.

.* ............................................................................
:h3 res=360 name=help_menu
    x=left y=bottom width=100% height=100%.Men£ Ayuda

El men£ Ayuda contiene las siguientes entradas&colon.

:parml compact tsize=10 break=none.
:pt.:hp2.Contenido:ehp2.
:pd.Este manual de usuario, desde el principio
:pt.:hp2.Teclas de funci¢n:ehp2.
:pd.Ayuda para operar el programa mediante el teclado
:pt.:hp2.Archivos PDF:ehp2.
:pd.Informaci¢n sobre el formato PDF y c¢mo :hp2.Lucide:ehp2. muestra diversos
tipos de PDFs
:pt.:hp2.Archivos de imagen:ehp2.
:pd.Informaci¢n sobre varios formatos de imagen soportados por Lucide
:pt.:hp2.Acerca de:ehp2.
:pd.Informaci¢n sobre :hp2.Lucide:ehp2.
:eparml.

.* ............................................................................
:h2 res=400 name=keyboard_accelerators
    x=left y=bottom width=100% height=100%.Teclas de funci¢n

Adem†s de las funciones de teclado est†ndar del sistema para controlar las
ventanas (p.e. Alt+F4 para cerrar, Alt+F5 para restaurar un tama§o intermedio,
Alt+F7 para mover, Alt+F8 para cambiar el tama§o, Alt+F9 para minimizar, etc.),
ciertas teclas de funci¢n espec°ficas (teclas r†pidas) ofrecen acceso inmediato
a muchas de las funciones de :hp2.Lucide:ehp2.&colon.

:hp2.
:table cols='18 48'.
:row.
:c.TECLA
:c.FUNCI‡N
:row.
:c.Ctrl+O
:c.abre el :link reftype=hd res=102.di†logo Abrir archivo:elink.
:row.
:c.Arriba
:c.cuando el :link reftype=hd res=008.panel de contenido:elink. o el :link
reftype=hd res=007.panel de navegaci¢n:elink. tienen el foco, desplazarlos
hacia arriba; si lo tienen el :link reftype=hd res=028.campo de entrada del
n£mero de p†gina de la barra de herramientas:elink. o el :link reftype=hd
res=112.di†logo Ir a la p†gina...:elink., incrementar el n£mero de p†gina
:row.
:c.Abajo
:c.cuando el :link reftype=hd res=008.panel de contenido:elink. o el :link
reftype=hd res=007.panel de navegaci¢n:elink. tienen el foco, desplazarlos
hacia arriba; si lo tienen el :link reftype=hd res=028.campo de entrada del
n£mero de p†gina de la barra de herramientas:elink. o el :link reftype=hd
res=112.di†logo Ir a la p†gina...:elink., decrementar el n£mero de p†gina
:row.
:c.Ctrl+May£s+Inicio
:c.abre el primer documento soportado en el directorio actual
:row.
:c.Ctrl+May£s+Fin
:c.abre el £ltimo documento soportado en el directorio actual
:row.
:c.Ctrl+May£s+ReP†g
:c.abre el anterior documento soportado en el directorio actual
:row.
:c.Ctrl+May£s+AvP†g
:c.abre el siguiente documento soportado en el directorio actual
:row.
:c.Ctrl+K
:c.va al :link reftype=hd res=217.£ltimo enlace seguido:elink.
:row.
:c.Ctrl+S
:c.guarda el documento actual (consulte :link reftype=hd res=219.Guardar...:elink.)
:row.
:c.Ctrl+A
:c.guarda el documento actual con otro nombre (consulte :link reftype=hd res=220.Guardar como...:elink.)
:row.
:c.Ctrl+F
:c.abre el :link reftype=hd res=108.di†logo Buscar:elink.
:row.
:c.Ctrl+I
:c.abre el :link reftype=hd res=114.contenedor Informaci¢n sobre el documento:elink.
:row.
:c.Ctrl+N
:c.abre el :link reftype=hd res=112.di†logo Ir a la p†gina:elink.
:row.
:c.Ctrl+P
:c.abre el :link reftype=hd res=104.di†logo Imprimir:elink.
:row.
:c.Ctrl+X
:c.cierra la ventana actual (consulte :link reftype=hd res=228.Salir:elink.)
:row.
:c.Ctrl+0
:c.:link reftype=hd res=262.Ajustar al alto de la ventana:elink.
:row.
:c.Ctrl+1
:c.:link reftype=hd res=263.Tama§o real:elink.
:row.
:c.Ctrl+2
:c.:link reftype=hd res=264.Ajustar al ancho:elink.
:row.
:c.+
:c.:link reftype=hd res=274.P†gina siguiente:elink.
:row.
:c.-
:c.:link reftype=hd res=273.P†gina anterior:elink.
:row.
:c.Ctrl++
:c.:link reftype=hd res=268.Aumentar tama§o:elink.
:row.
:c.Ctrl+-
:c.:link reftype=hd res=269.Disminuir tama§o:elink.
:row.
:c.Ctrl+Shift++
:c.rota 90&deg. a la derecha la vista actual (consulte :link reftype=hd
res=280.Rotar 90&deg. en sentido horario:elink.)
:row.
:c.Ctrl+Shift+-
:c.rota 90&deg. a la izquierda la vista actual (consulte :link reftype=hd
res=281.Rotar 90&deg. en sentido antihorario:elink.)
:row.
:c.Ctrl+/
:c.selecciona todo el contenido de la vista actual
:row.
:c.Ctrl+Ins
:c.copia el contenido seleccionado al †rea com£n
:row.
:c.F1
:c.muestra la ayuda
:row.
:c.F5
:c.alterna la vista actual y el modo :link reftype=hd res=304.Presentaci¢n:elink.
:row.
:c.F9
:c.muestra/oculta el :link reftype=hd res=007.Panel de navegaci¢n:elink.
:row.
:c.F10
:c.accede al men£
:row.
:c.F11
:c.alterna la vista actual y el modo :link reftype=hd res=303.Pantalla completa:elink.
:row.
:c.Ctrl+F4
:c.cierra el documento actual (consulte :link reftype=hd res=222.Cerrar:elink.)
:etable.
:ehp2.

.* ............................................................................
:h2 res=420 name=mouse
    x=left y=bottom width=100% height=100%.Acciones y botones del rat¢n

Los botones y acciones del rat¢n disponibles en :hp2.Lucide:ehp2. permiten
acceder a las siguientes funciones&colon.

:hp2.
:table cols='15 48'.
:row.
:c.ACCI‡N
:c.FUNCI‡N
:row.
:c.BR1
:c.selecciona un elemento dado de un men£ o formulario, o si se ha seleccionado
la herramienta :link reftype=hd res=034.Aumentar/reducir tama§o:elink. y el
puntero ha cambiado a una lupa, aumenta el tama§o
:row.
:c.BR2
:c.si se ha seleccionado la herramienta :link reftype=hd
res=034.Aumentar/reducir tama§o:elink. y el puntero ha cambiado a una lupa,
disminuye el tama§o
:row.
:c.arrastrar BR1
:c.selecciona parte del contenido del documento al arrastrar a lo largo del
texto o el margen (o fuera de Çl) para seleccionar l°neas o secciones enteras.
:row.
:c.arrastrar BR2
:c.si no se ha seleccionado la herramienta :link reftype=hd
res=034.Aumentar/reducir tama§o:elink. el puntero cambia a la mano de desplazar
y mueve la secci¢n mostrada en el :link reftype=hd res=008.panel de
contenido:elink..
:etable.
:ehp2.

.* ............................................................................
:h2 res=440 name=remote_control
    x=left y=bottom width=100% height=100%.Funciones de control remoto

La primera instancia de :hp2.Lucide:ehp2. crea un canal (o Ænamed pipeØ) llamado
Æ\PIPE\LUCIDEØ. Desde ese momento se pueden enviar los siguientes mandatos a
dicho canal&colon.

:hp2.
:table cols='15 48'.
:row.
:c.MANDATO
:c.ACCI‡N
:row.
:c.&dollar.prev
:c.cambiar a la p†gina anterior
:row.
:c.&dollar.next
:c.cambiar a la siguiente p†gina
:row.
:c.&dollar.presentation
:c.cambiar a modo presentaci¢n (incluso minimizado)
:row.
:c.&dollar.minimize
:c.mimimiza Lucide (incluso desde pantalla completa)
:row.
:c.&dollar.rotate
:c.rotar 90 grados en sentido horario
:row.
:c.&dollar.zoomin
:c.aumentar tama§o
:row.
:c.&dollar.zoomout
:c.disminuir tama§o
:row.
:c.&dollar.zoomoriginal
:c.pasar a tama§o real
:etable.
:ehp2.

.* ............................................................................
:h2 res=500 name=howto
    x=left y=bottom width=100% height=100%.®C¢mo se...

:hp2.®C¢mo se...:ehp2.

:ul compact.
:li.:link reftype=hd res=502.selecciona contenido?:elink.
:li.:link reftype=hd res=504.busca texto?:elink.
:li.:link reftype=hd res=506.cumplimentan formularios PDF?:elink.
:li.:link reftype=hd res=508.controla Lucide remotamente?:elink.
:li.:link reftype=hd res=510.configura Lucide para abrir enlaces?:elink.
:li.:link reftype=hd res=512.desactiva la creaci¢n autom†tica de miniaturas?:elink.
:li.:link reftype=hd res=513.elimina la miniatura de un archivo?:elink.
:li.:link reftype=hd res=514.controlan la salida y distribuci¢n de impresi¢n?:elink.
:li.:link reftype=hd res=580.puede conseguir ayuda con un problema?:elink.
:li.:link reftype=hd res=582.solicitan mejoras al programa?:elink.
:li.:link reftype=hd res=584.involucra uno en el proyecto Lucide?:elink.
:eul.

.* ............................................................................
:h3 res=502 name=select_content
    x=left y=bottom width=100% height=100%.selecciona contenido?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.selecciona contenido?:ehp2.

:p.Seleccionar texto en un PDF se logra bien arrastrando el primer bot¢n del
rat¢n sobre el texto que se va a seleccionar (o por el margen), seleccionando
todo el texto de la vista actual mediante Editar &rarrow. Seleccionar todo o
utilizando la combinaci¢n de teclas est†ndar de OS/2, :hp2.Ctrl+/:ehp2..

:p.Actualmente no es posible seleccionar los elementos no textuales de una
p†gina.

:nt.Otros m¢dulos pueden permitir seleccionar distintos tipos de elementos.
Consulte la documentaci¢n para m¢dulos espec°ficos para determinar sus
capacidades y c¢mo utilizarlas.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=242.Copiar:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=420.Uso del rat¢n:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h3 res=504 name=search_text
    x=left y=bottom width=100% height=100%.busca texto?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.busca texto?:ehp2.

:p.Buscar texto en un PDF se hace mediante el :link reftype=hd res=108.di†logo
Buscar:elink., al que se accede de las siguientes formas&colon.

:ul compact.
:li.:link reftype=hd res=246.Buscar...:elink.
:li.:link reftype=hd res=108.Di†logo Buscar:elink.
:li.:link reftype=hd res=400.Combinaci¢n de teclas Ctrl+F:elink.
:eul.

:nt.Algunos m¢dulos pueden no permitir buscar texto. Consulte la documentaci¢n
para m¢dulos espec°ficos para determinar sus capacidades y c¢mo
utilizarlas.:ent.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=242.Copiar:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h3 res=506 name=pdf_form_fill-in
    x=left y=bottom width=100% height=100%.cumplimentan formularios PDF?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.cumplimentan formularios PDF?:ehp2.

:p.Introducir datos en un formulario PDF es tan sencillo como teclear en los
campos disponibles en el formulario. Actualmente, cuando se ha cambiado un
documento al introducir datos en Çl (no necesariamente en todos los campos), al
salir o cerrar la ventana :hp2.Lucide:ehp2. preguntar† si guardar el documento
con un nuevo nombre.

:p.Aunque generalmente no se permite ÆpegarØ en :hp2.Lucide:ehp2., es posible
pegar datos del †rea com£n del sistema en los campos del formulario mediante
las combinaciones de teclas est†ndar de OS/2 y tambiÇn se puede utilizar
:hp2.Ctrl+V:ehp2., :hp2.Ctrl+C:ehp2. y :hp2.Ctrl+X:ehp2. para copiar y pegar
los datos introducidos en el formulario adem†s de las combinaciones
convencionales de OS/2 :hp2.Ctrl+Ins:ehp2. y :hp2.May£s+Supr:ehp2..

:caution.Por consideraciones de privacidad y seguridad, no edite un documento
con formularios ya cumplimentados. Al hacerlo, se guardan los datos antiguos y
los nuevos en el archivo resultante, potencialmente exponiendo informaci¢n
sensible. Comience siempre con un formulario PDF limpio. êsta es una limitaci¢n
impuesta por la biblioteca de c¢digo Poppler que Lucide utiliza actualmente
para mostrar los documentos PDF.:ecaution.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=420.Uso del rat¢n:elink.
.br
:link reftype=hd res=400.Teclas:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h3 res=508 name=controlling_remotely
    x=left y=bottom width=100% height=100%.controla Lucide remotamente?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.controla Lucide remotamente?:ehp2.

:p.Cualquier entidad capaz de enviar datos mediante canales (Ænamed pipesØ)
localmente o a travÇs de la red deber°a poder dirigir mandatos a Lucide. Para
una referencia completa de los mandatos reconocidos por Lucide, consulte :link
reftype=hd res=440.Funciones de control remoto:elink..

:p.Esto puede resultar £til para presentaciones con un mando a distancia, por
ejemplo.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=028.Controles de navegaci¢n:elink.
:edl.

.* ............................................................................
:h3 res=510 name=opening_hyperlinks
    x=left y=bottom width=100% height=100%.configura Lucide para abrir enlaces?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.configura Lucide para abrir enlaces?:ehp2.

:p.Los enlaces en documentos PDF pueden activar otros puntos del mismo
documento, contenido web, la redacci¢n de correos o incluso otros documentos
PDF. Cuando se sit£a el cursor del rat¢n sobre uno, el puntero cambia a la mano
:artwork runin name='hand.bmp'.&per. Pulse el primer bot¢n del rat¢n sin m†s
para seguir el enlace.

:p.Para abrir adecuadamente hiperenlaces (a la web o redacci¢n de mensajes), es
necesario asegurarse de que las aplicaciones por omisi¢n para el Worplace
Shell de OS/2 se hayan configurado adecuadamente. :hp2.Lucide:ehp2. pasar† la
ubicaci¢n de destino del enlace a la aplicaci¢n configurada.

:p.Los enlaces dirigidos a otros documentos PDF pueden comportarse o no como se
espera debido a una variedad de factores, incluido quÇ aplicaci¢n se utiliz¢
para crear el documento actual y c¢mo se hayan definido los enlaces. Hay
planeadas mejoras para esta funci¢n.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=008.Panel de contenido:elink.
.br
:link reftype=hd res=740.Enlaces en PDF:elink.
.br
:link reftype=hd res=217.Èltimo enlace seguido:elink.
:edl.

.* ............................................................................
:h3 res=512 name=disable_thumbnails
    x=left y=bottom width=100% height=100%.desactiva la creaci¢n autom†tica de miniaturas?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.desactiva la creaci¢n autom†tica de miniaturas?:ehp2.

:p.Si as° se configura, al abrir un archivo soportado, :hp2.Lucide:ehp2. crea
una imagen en miniatura del archivo e intenta almacenarla en los atributos
extendidos del archivo (suponiendo que el archivo se haya abierto desde un medio
escribible, se tengan permisos para modificar archivos en el directorio, y el
sistema de archivos soporte atributos extendidos).

:p.Sin embargo, este comportamiento puede no ser siempre deseable, por ejemplo
si el documento contiene informaci¢n sensible. Para desactivar la creaci¢n de
miniaturas por omisi¢n, marque la casilla correspondiente en el :link
reftype=hd res=110.di†logo Preferencias:elink.. Para desactivar la creaci¢n de
la vista en miniatura para un archivo espec°fico (si est† activa globalmente),
desmarque la casilla :hp2.Crear miniatura:ehp2. en el :link reftype=hd
res=102.di†logo Abrir archivo:elink. al abrirlo.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=102.Di†logo Abrir archivo:elink.
.br
:link reftype=hd res=110.Di†logo Preferencias:elink.
.br
:link reftype=hd res=730.Seguridad PDF:elink.
.br
:link reftype=hd res=840.Seguridad:elink.
.br
:link reftype=hd res=513.Eliminar miniaturas:elink.
:edl.

.* ............................................................................
:h3 res=513 name=remove_thumbnails
    x=left y=bottom width=100% height=100%.elimina la miniatura de un archivo?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.elimina la miniatura de un archivo?:ehp2.

:p.Las versiones anteriores de :hp2.Lucide:ehp2. no permit°an desactivar la
creaci¢n de miniaturas. Por tanto, pueden haberse creado miniaturas incluso
para PDFs protegidos que podr°an haber contenido informaci¢n sensible. Una
forma de eliminarlas es utilizar el excelente del_ea.cmd de Heiko Nitzsche,
disponible en Hobbes&colon.

:p.http&colon.//hobbes.nmsu.edu/h-search.php?key=del_ea&amp.pushbutton=Search

:p.Otra forma es utilizar la herramienta EAUTIL.EXE incluida con OS/2 para
separar los atributos extendidos del archivo con la opci¢n /S, utilizando la
siguiente sintaxis desde un indicador de mandatos&colon.

:p.[C&colon.\]EAUTIL /S &lt.:hp1.nombre.ext:ehp1.&gt. nul

:p.Hay muchas otras formas de suprimir los atributos extendidos (y, por tanto,
las miniaturas).

:caution.
Si se han almacenado m†s datos en los atributos extendidos, los procedimientos
anteriores provocar†n la pÇrdida de dichos datos.
:ecaution.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=512.Desactivar crear miniaturas:elink.
.br
:link reftype=hd res=102.Di†logo Abrir archivo:elink.
.br
:link reftype=hd res=110.Di†logo Preferencias:elink.
.br
:link reftype=hd res=730.Seguridad PDF:elink.
.br
:link reftype=hd res=840.Seguridad:elink.
:edl.

.* ............................................................................
:h3 res=514 name=directing_output
    x=left y=bottom width=100% height=100%.controlan la salida y distribuci¢n de impresi¢n?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.controlan la salida y distribuci¢n de impresi¢n?:ehp2.

:p.Desde el :link reftype=hd res=104.di†logo Imprimir:elink., es posible
seleccionar la impresora que procesar† la salida del documento actual.
Hay disponibles en el di†logo opciones para seleccionar rangos y †mbito
de impresi¢n de p†ginas pares/impares, pero las opciones m†s avanzadas deber†n
seleccionarse al nivel del trabajo de impresi¢n. Para hacer esto, pulse el
bot¢n Propiedades del trabajo, que abre el cuaderno de propiedades del sistema
del trabajo de impresi¢n. El controlador de impresi¢n deber°a proporcionar
opciones de distribuci¢n de las p†ginas (cuadernillo, por pares, cuartos,
d£plex, etc.).

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=024.Imprimir...:elink.
.br
:link reftype=hd res=224.Imprimir...:elink.
.br
:link reftype=hd res=104.Di†logo Imprimir:elink.
:edl.

.* ............................................................................
:h3 res=580 name=get_help
    x=left y=bottom width=100% height=100%.puede conseguir ayuda con un problema?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.puede conseguir ayuda con un problema?:ehp2.

:p.:hp2.Lucide:ehp2. es un proyecto de Netlabs. El punto de partida para la
resoluci¢n de problemas es la ÆwikiØ de :hp2.Lucide:ehp2.&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.Si el problema que est† experimentando no se ha abordado en la wiki, abra
con entera libertad una incidencia (en inglÇs) en el sistema de seguimiento de
errores&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.o £nase a las listas de correo de Lucide (en inglÇs) siguiendo las
instrucciones detalladas en la wiki.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=900.Referencias:elink.
.br
:link reftype=hd res=582.Nuevas funciones:elink.
.br
:link reftype=hd res=584.Involucrarse en el proyecto:elink.
:edl.

.* ............................................................................
:h3 res=582 name=feature_requests
    x=left y=bottom width=100% height=100%.solicitan mejoras al programa?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.solicitan mejoras al programa?:ehp2.

:p.:hp2.Lucide:ehp2. es un proyecto de Netlabs. El punto de partida para la
resoluci¢n de problemas es la ÆwikiØ de :hp2.Lucide:ehp2.&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.Si la funci¢n que echa de menos no se ha abordado en la wiki, abra con
entera libertad una incidencia (en inglÇs) para solicitarla en el sistema de
seguimiento de errores&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.o £nase a las listas de correo de Lucide (en inglÇs) siguiendo las
instrucciones detalladas en la wiki.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=900.Referencias:elink.
.br
:link reftype=hd res=580.Problemas:elink.
.br
:link reftype=hd res=584.Involucrarse en el proyecto:elink.
:edl.

.* ............................................................................
:h3 res=584 name=get_involved
    x=left y=bottom width=100% height=100%.involucra uno en el proyecto Lucide?

:hp2.®C¢mo se...:ehp2.

:p.:hp2.involucra uno en el proyecto Lucide?:ehp2.

:p.:hp2.Lucide:ehp2. es un proyecto de Netlabs. Como tal, es un esfuerzo
completamente voluntario. Adem†s de contribuir c¢digo, el trabajo de traducci¢n
y documentaci¢n consume mucho tiempo aunque es extremadamente valioso para
hacer que :hp2.Lucide:ehp2. sea todo lo que puede ser. Se agradece tambiÇn la
contribuci¢n de contenido a la wiki o investigar nuevas formas mejores para
realizar las tareas. El punto de partida para involucrarse es la wiki de
:hp2.Lucide:ehp2.&colon.

:p.https&colon.//trac.netlabs.org/lucide/

:p.Unirse a las listas de correo de Lucide (en inglÇs) siguiendo las
instrucciones detalladas en la wiki es otra gran forma de comenzar.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=900.Referencias:elink.
.br
:link reftype=hd res=580.Problemas:elink.
.br
:link reftype=hd res=582.Nuevas funciones:elink.
:edl.

.* ............................................................................
:h1 res=700 name=concepts
    x=left y=bottom width=100% height=100%.Conceptos

:hp2.Lucide:ehp2. es un visor de documentos con arquitectura modular que
soporta distintos formatos de archivo, principalmente PDF (Portable Document
Format) de Adobe. La arquitectura de sus m¢dulos o ÆpluginsØ est† basada en
SOM, lo que permite a terceros programadores a§adir f†cilmente soporte para m†s
formatos.

:p.Es £til entender algunos de los conceptos asociados con los diversos tipos
de documentos a los que :hp2.Lucide:ehp2. da soporte y c¢mo el programa
presenta los datos de forma diferente seg£n el tipo de archivo.

:ul compact.
:li.:link reftype=hd res=710.Tipos de documentos PDF:elink.
:li.:link reftype=hd res=720.Formularios PDF:elink.
:li.:link reftype=hd res=730.Seguridad PDF:elink.
:li.:link reftype=hd res=740.Enlaces en PDF:elink.
:li.:link reftype=hd res=780.Formatos de imagen:elink.
:eul.

.* ............................................................................
:h2 res=710 name=pdf_types
    x=left y=bottom width=100% height=100%.Tipos de documentos PDF

:hp2.Lucide:ehp2. es capaz de manejar cierta variedad de tipos de archivos PDF.
Es £til entender algunas de las diferencias entre ellos.

:ul compact.
:li.:link reftype=hd res=712.En general:elink.
:li.:link reftype=hd res=714.Fuentes: inclusi¢n y sustituci¢n:elink.
:li.:link reftype=hd res=716.Variantes de PDF:elink.
:eul.

.* ............................................................................
:h3 res=712 name=pdf_types_in_general
    x=left y=bottom width=100% height=100%.En general

Los archivos PDF (Portable Document Format) caen por lo general en una de estas
tres categor°as&colon.

:ul compact.
:li.ÆverdaderosØ o creados digitalmente: el documento tiene su origen en un
procesador de textos u otra aplicaci¢n que genera texto e/o im†genes como
salida ÆimpresaØ;
:li.digitalizaci¢n o de imagen: el documento es esencialmente una fotograf°a
(o conjunto de ellas) de un documento f°sico, y se presenta como archivo de
imagen; o
:li.mixto: un documento que comenz¢ como imagen pero fue procesado a posteriori
para reconocer el texto contenido en las im†genes e incorporarlo como elemento
susceptible de b£squedas.
:eul.

:p.Los formularios son variantes del primer tipo, y pueden dividirse en otro
conjunto de categor°as. Para una discusi¢n m†s detallada de los formularios
PDF, por favor consulte m†s tarde :link reftype=hd res=720.Formularios
PDF:elink..

:p.Actualmente, :hp2.Lucide:ehp2. puede representar estos tres tipos
principales de archivos PDF, con algunas excepciones. El rango de formularios
procesables se ampl°a con cada versi¢n, sin embargo, de modo que en alg£n
momento Lucide deber°a deber°a poder mostrar correctamente todos los tipos de
PDF, incluidos aquellos menos comunes que pueden causar alg£n problema en la
actualidad.

.* ............................................................................
:h3 res=714 name=pdf_fonts
    x=left y=bottom width=100% height=100%.Fuentes: inclusi¢n y sustituci¢n

Un PDF verdadero puede gestionar las fuentes de una o m†s de las siguientes
formas&colon.

:ul compact.
:li.sustituci¢n, que hace que Lucide muestre Æal vueloØ una imagen general
utilizando la informaci¢n del documento sobre los caracteres;
:li.inclusi¢n, en la que todos los caracteres necesarios para representar una
fuente se incluyen en el propio documento;
:li.inclusi¢n parcial, en la que s¢lo se incluyen en el documento los
caracteres de las fuentes que aparecen en el mismo.
:eul.

:p.Puesto que una fuente puede constar de miles de caracteres, incluir s¢lo los
caracteres realmente utilizados en cada documento espec°fico redundar† en
archivos de tama§o m†s peque§o, lo m†s deseable normalmente.

:p.Normalmente, la sustituci¢n produce los tama§os de archivo m†s peque§os; sin
embargo, puede causar problemas para el archivado de documentos u otras
situaciones en las que se necesita absoluta fidelidad al material original. Las
fuentes no est†ndar o, por ejemplo, los s°mbolos matem†ticos pueden no mostrarse
lo bastante fidedignamente para una representaci¢n adecuada de los datos.

:p.La inclusi¢n almacena las fuentes enteras en el documento PDF, lo que
normalmente produce los mayores archivos, si bien los m†s fieles al material
original.

:p.La inclusi¢n parcial proporciona un equilibrio entre tama§o de archivo y
fidelidad, puesto que representa exactamente todos los caracteres utilizados en
el documento, mientras se minimiza el espacio que se desperdiciar°a en el documento
dedic†ndolo a caracteres y fuentes que no se utilizan.

:p.El m¢dulo PDF incluido con :hp2.Lucide:ehp2. utiliza la :link refid=poppler
reftype=fn.biblioteca de c¢digo externa ÆPopplerØ:elink. para mostrar los
documentos PDF. Poppler, a su vez, utiliza la misma :link refid=fontconfig
reftype=fn.biblioteca Fontconfig:elink. que las aplicaciones Mozilla actuales
para realizar sustituci¢n de fuentes por nombre, de modo que se puedan
seleccionar fuentes alternativas apropiadas para los documentos que no incluyen
fuentes.

:p.Dependiendo de las fuentes instaladas en el sistema actualmente, algunas
fuentes sustitutas pueden funcionar mejor que otras. Fontconfig hace una
determinaci¢n razonable al seleccionar una fuente alternativa; sin embargo, la
selecci¢n disponible es clave. Tener un conjunto de fuentes robusto en el
sistema puede suponer la diferencia entre un documento legible o uno al que le
falte contenido o sea dif°cil -si no imposible- de leer.

:p.Adem†s de mostrarlos, deber°a tenerse en cuenta que la b£squeda global de
texto en :hp2.Lucide:ehp2. s¢lo es posible en documentos PDF verdaderos o
mixtos, en los que hay texto como tal disponible para realizar b£squedas. Esto
no es posible con los PDFs de tipo imagen.

:fn id=poppler.
Poppler es una biblioteca de representaci¢n de PDF basada en el c¢digo de
xpdf-3.0.

:p.P†gina en Internet&colon.
.br
https&colon.//poppler.freedesktop.org/

:p.Informar de errores en Poppler&colon.
.br
https&colon.//bugs.freedesktop.org/buglist.cgi?query_format=specific&amp.order=relevance+desc&amp.bug_status=__open__&amp.product=poppler&amp.content=

:p.P†gina de Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/Poppler_%28software%29
:efn.

:fn id=fontconfig.
Fontconfig es una biblioteca para configurar y personalizar el acceso a
fuentes.

:p.P†gina en Internet&colon.
.br
https&colon.//www.fontconfig.org/

:p.Informar de errores en Fontconfig&colon.
.br
https&colon.//bugs.freedesktop.org/buglist.cgi?bug_status=__open__&amp.order=relevance%20desc&amp.product=fontconfig&amp.query_format=specific
:efn.

.* ............................................................................
:h3 res=716 name=pdf_variants
    x=left y=bottom width=100% height=100%.Variantes de PDF

ÆPDFØ es el tÇrmino com£n utilizado para describir todos los archivos de tipo
Portable Document Format; sin embargo, hay cierto n£mero de subdivisiones de
dicha tecnolog°a y :link refid=iso_32000-1 reftype=fn.el propio est†ndar
PDF:elink. ha sufrido muchos cambios a lo largo de su historia.

:p.Los documentos PDF Æest†ndarØ (que cumplen la norma ISO 32000-1) se deber°an
poder leer con :hp2.Lucide:ehp2. de forma general. Estos documentos permiten la
inclusi¢n y sustituci¢n de fuentes; sin embargo, pueden incluir algunos
elementos XFA (XML Forms Architecture) que a£n no se manejan bien en Poppler y,
por extensi¢n, :hp2.Lucide:ehp2.. Para una discusi¢n m†s detallada de los
formularios PDF, por favor consulte m†s tarde :link reftype=hd
res=720.Formularios PDF:elink..

:p.:link refid=iso_19005 reftype=fn.PDF/A:elink. es un subconjunto de PDF que
intenta eliminar ciertos riesgos a la fidelidad documental. Por ejemplo, PDF/A
no permite el contenido din†mico (fuentes u otros medios sustituidos), lo que
lo convierte en la elecci¢n id¢nea para mantener archivos. Todos los datos
necesarios para representar el documento se incluyen est†n contenidos en el
archivo PDF/A, incluidos fuentes, perfiles de color, im†genes, etc.

:p.:hp2.Lucide:ehp2. deber°a manejar los documentos PDF/A como cualesquiera
otros, aunque los PDF/A tienden a ser de mayor tama§o que algunos otros y
por tanto tardan m†s en cargarse y necesitan mayor potencia de proceso para
examinarse.

:p.:link refid=iso_24517-1 reftype=fn.PDF/E:elink., otro subconjunto de PDF, se
proyect¢ para documentaci¢n tÇcnica y de ingenier°a. Se basa en la PDF Reference
versi¢n 1.6 de Adobe Systems y soporta medios interactivos, incluidas im†genes
3D y animaci¢n.

:p.:link refid=iso_14739-1 reftype=fn.PRC:elink. (Product Representation
Compact) se define dentro de PDF/E-2 como un formato de archivo de alta
compresi¢n para contenido 3D, proyectado para incluirse en documentos PDF y
otros formatos similares orientados al intercambio y representaci¢n 3D. Se
puede utilizar para crear, ver y distribuir datos 3D en flujos de trabajo de
intercambio de documentos. Est† optimizado para almacenar, cargar y mostrar
varias clases de datos 3D, especialmente los que vienen de sistemas de dise§o
asistido por ordenador (CAD: computer aided design).

:p.:link refid=ecma-363 reftype=fn.U3D:elink. es otro formato de archivo
comprimido que se puede utilizar desde PDF/E. U3D publicado y mantenido por
ECMA International como ECMA-363.

:p.:hp2.Lucide:ehp2. deber°a poder abrir los documentos PDF/E 2D como se
espera, aunque no se podr† reproducir el contenido multimedia. De la misma
forma no se representar†n los archivos 3D incluidos en formato U3D ni PRC.
Adem†s s¢lo se representar† una capa de los documentos PDF/E multicapa.

:p.:link refid=iso_14289-1 reftype=fn.PDF/UA:elink. (Universal Access) ofrece
accesibilidad para gente con discapacidades que utiliza lectores de pantalla,
lupas para pantalla, joysticks, etc. para examinar y leer documentos
electr¢nicos.

:p.:hp2.Lucide:ehp2. es capaz de mostrar el contenido textual de los documentos
PDF/UA, aunque actualmente :hp2.Lucide:ehp2. carece de cualquier tipo de
mecanismo para pasar los datos a un lector de pantalla, por ejemplo.
:hp2.Lucide:ehp2. interpreta el texto de un documento PDF/UA como un gran
enlace y el puntero del rat¢n ser† siempre la mano :artwork runin
name='hand.bmp'.&per.

:p.:link refid=iso_16612-2 reftype=fn.PDF/VT:elink. (Variable y Transactional)
se define sobre PDF/X-4 y PDF/X-5, utilizando PDF 1.6. Es el primer formato de
impresi¢n de datos variables (VDP: variable-data printing) que asegura una
gesti¢n moderna del color :link refid=icc reftype=fn.basada en ICC:elink.
utilizando ICC Output Intents. A§ade el concepto de grupos de objetos gr†ficos
encapsulados para soportar el procesamiento optimizado de contenido textual o
de im†genes repetido. A travÇs de metadatos de partes de documentos (DPM:
Document Part Metadata) se puede lograr una gesti¢n din†mica y fiable de
p†ginas para datos de impresi¢n de alto volumen de salida transaccional (HVTO:
High Volume Transactional Output), p.e. selecci¢n de registros u optimizaci¢n
de portes basadas en tales metadatos.

:p.PDF/VT-1 siempre consiste en un £nico archivo autocontenido, aunque otras
variantes del est†ndar permiten contenido gr†fico externo (PDF/VT-2), y los
PDF/VT-2s ofrecen transmisi¢n de datos en tiempo real mediante el uso de
paquetes MIME compuestos. Tales documentos se pueden compartir, mostrar o
navegar de forma interactiva utilizando programas visores de PDF est†ndar
(tales como :hp2.Lucide:ehp2.), aunque la verdadera fidelidad requiere
programas que cumplan con PDF/X-4 o PDF/VT (una versi¢n futura de Poppler
puede ser totalmente conforme).

:p.Debido a la naturaleza completamente encapsulada de los documentos PDF/VT-1,
:hp2.Lucide:ehp2. puede mostrarlos fielmente, aunque de los PDF/VT-2 (y, por
extensi¢n, PDF/VT-2s) s¢lo se mostrar† el documento seleccionado
actualmente y no ninguno de sus componentes documentales externos enlazados.
Esto puede abordarse en una versi¢n futura de Poppler.

:p.:link refid=iso_15930 reftype=fn.PDF/X:elink. se parece a PDF/A en que
tambiÇn debe contener datos encapsulados; sin embargo, puesto que el principal
prop¢sito de PDF/X es gestionar el intercambio de gr†ficos, tiene algunas
necesidades relacionadas con la impresi¢n que van m†s all† del †mbito de los
PDFs est†ndar. Adem†s de encapsular im†genes, cuando son conformes con la
especificaci¢n PDF/X-1a (basada originalmente en PDF 1.3, con la actualizaci¢n
de 2003 basada en PDF 1.4), tales im†genes deben ser en cuatricrom°a o colores
directos. Los colores calibrados CIELAB o RGB son aceptables para la
conformidad con PDF/X-3 (basado en PDF 1.4), aunque permanecen la mayor°a de
los otros requisitos de PDF/X-1a. (Nunca se lleg¢ a publicar PDF/X-2.)

:p.PDF/X-4 ofrece soporte de datos de color gestionado, cuatricrom°a, gris,
tricrom°a, o color directo, adem†s de transparencia y contenido opcional en los
que los datos est†n contenidos en el archivo. Se utiliza un segundo nivel de
conformidad (PDF/X-4p, basado en PDF 1.6) para designar un documento PDF/X-4 en
el que se suministra externamente un perfil ICC necesario que se identifica de
forma un°voca.

:p.PDF/X-5 (basado en PDF 1.6) permite que se incluyan todos los datos, o donde
se haya previsto que se identifique de forma un°voca y se suministre
externamente contenido gr†fico o perfiles ICC de n colorantes. Este est†ndar se
actualiz¢ en 2010 con peque§as correcciones que no alteraron la especificaci¢n
original.

:p.PDF/X-5 ofrece tres niveles de conformidad&colon.

:ul.
:li.PDF/X-5g&colon., que extiende PDF/X-4, habilitando el uso de contenido
gr†fico externo (flujos de trabajo estilo interfaz de preimpresi¢n abierta: OPI,
u Open Prepress Interface). M†s espec°ficamente, pueden referenciarse gr†ficos
externos al PDF que Æpueden tener valor al... reducir... las exigencias...
permitiendo... trabajar a baja resoluci¢nØ [ISO-15930-8&colon.2010].

:li.PDF/X-5pg&colon., que extiende PDF/X-4p, habilitando el uso de contenido
gr†fico externo junto a una referencia a un perfil ICC externo a la salida
buscada.

:li.PDF/X-5n&colon., que extiende PDF/X-4p, habilitando un perfil ICC
suministrado externamente a la salida buscada para usar un espacio de color que
no sea escala de grises, tricrom°a RGB o cuatricrom°a CMYK.
:eul.

:p.Los documentos PDF/X tambiÇn deben incluir un archivo especial de
identificaci¢n que especifique con quÇ nivel de PDF/X son conformes. Un archivo
dado s¢lo puede ser conforme con un £nico est†ndar PDF/X.

:p.:hp2.Lucide:ehp2. deber°a ser capaz de abrir documentos PDF/X as° como
PDF/A, ya que el contenido encapsulado deber°a tener soporte completo en
Poppler.

.* ............................................................................
:fn id=icc.
El formato de perfil del International Color Consortium&lnotrev. ofrece un
formato de perfil de dispositivo multiplataforma. Se pueden utilizar los
perfiles de dispositivo para traducir datos de color creados en un dispositivo
al espacio de color nativo de otro dispositivo. La aceptaci¢n de este formato
por parte de los creadores de sistemas operativos permite a los usuarios
finales mover transparentemente entre distintos sistemas operativos perfiles e
im†genes con perfiles encapsulados.

:p.El International Color Consortium&colon.
.br
http&colon.//www.color.org/

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/International_Color_Consortium
:efn.

.* ............................................................................
:fn id=iso_32000-1.
Aunque desarrollado originalmente por Adobe Systems, desde 2008, PDF como
est†ndar lo mantiene la Organizaci¢n Internacional de Estandarizaci¢n (ISO)
como ISO 32000-1&colon.2008. El texto completo del est†ndar est† disponible
en&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=51502

:p.PDF est† bajo supervisi¢n de la PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/Portable_Document_Format
:efn.

.* ............................................................................
:fn id=iso_19005.
PDF/A es un est†ndar ISO que hasta ahora ha tenido tres revisiones
importantes&colon.
.br
PDF/A-1&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=60603
.br
PDF/A-2&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=50655
.br
PDF/A-3&colon. http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=57229

:p.PDF/A est† bajo supervisi¢n de la PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/A
:efn.

.* ............................................................................
:fn id=iso_24517-1.
ISO 24517-1&colon.2008 se basa en la PDF Reference versi¢n 1.6 de Adobe
Systems&colon.
.br
https&colon.//www.adobe.com/devnet/pdf/pdf_reference_archive.html

:p.El documento de est†ndares ISO se encuentra en&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=42274

:p.PDF/E est† bajo supervisi¢ de la PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.P†gina de Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/E
:efn.

.* ............................................................................
:fn id=iso_14739-1.
PRC (ISO 14739-1&colon.2014) se define como parte del PDF/E-2.

:p.El documento de est†ndares ISO se encuentra en&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=54948

:p.PRC est† bajo supervisi¢n del 3DPDF Consortium&colon.
http&colon.//www.3dpdfconsortium.org/

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/PRC_%28file_format%29
:efn.

.* ............................................................................
:fn id=ecma-363.
U3D (ECMA-363) es un formato de archivo para contenido 3D que, como el PRC,
se puede encapsular en documentos PDF/E-2.

:p.El documento de Est†ndares internacionales de ECMA se encuentra en&colon.
.br
http&colon.//www.ecma-international.org/publications/standards/Ecma-363.htm

:p.U3D est† bajo supervisi¢n del 3DPDF Consortium&colon.
.br
http&colon.//www.3dpdfconsortium.org/

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/Universal_3D
:efn.

.* ............................................................................
:fn id=iso_14289-1.
ISO 14289-1&colon.2014, la segunda revisi¢n del est†ndar publicado
originalmente en 2012, es el primer documento de est†ndares disponible
libremente de la ISO, y en s° mismo es un documento PDF/UA&colon.
.br
http&colon.//www.iso.org/iso/catalogue_detail.htm?csnumber=54564

:p.PDF/UA est† bajo supervisi¢n de la PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.La PDF Association tambiÇn mantiene una bater°a de pruebas de
conformidad con PDF/UA, llamada El Protocolo Matterhorn&colon.
.br
http&colon.//www.pdfa.org/publication/the-matterhorn-protocol-1/

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/UA
:efn.

.* ............................................................................
:fn id=iso_16612-2.
PDF/VT-2&colon.2010 (que engloba PDF/VT-1) es un est†ndar ISO&colon.
.br
http&colon.//www.iso.org/iso/iso_catalogue/catalogue_tc/catalogue_detail.htm?csnumber=46428

:p.PDF/VT est† bajo supervisi¢n de la PDF Association&colon.
.br
http&colon.//www.pdfa.org/

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/VT
:efn.

.* ............................................................................
:fn id=iso_15930.
PDF/X es un est†ndar ISO que hasta ahora ha pasado por las siguientes
revisiones y extensiones&colon.
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

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/PDF/X
:efn.


.* ............................................................................
:h2 res=720 name=pdf_forms
    x=left y=bottom width=100% height=100%.Formularios PDF

Los archivos PDFs cumplimentables son principalmente de dos tipos&colon.

:ul.
:li.AcroForms, creados generalmente con las versiones de Adobe Acrobat 4.x
hasta 7.x
:li.Basados en formularios XFA (XML Forms Architecture), desarrollados por
Accellio, que fue absorbida despuÇs por Adobe. Estos documentos almacenan la
estructura de datos XML dentro del archivo PDF y ahora son el mÇtodo est†ndar
de crear documentos PDF con formularios. Adobe LiveCycle Designer 7.x o m†s
reciente, as° como las versiones de Acrobat posteriores a 7.x crean formularios
basados en XFA.
:eul.

:p.:hp2.Lucide:ehp2. es capaz de manejar ambos tipos de formularios PDF,
aunque conviene adoptar algunas precauciones. Al guardar los datos de un
formulario a un documento basado en XFA, la biblioteca Poppler que
:hp2.Lucide:ehp2. utiliza los almacena en el archivo PDF y :hp2.Lucide:ehp2.,
al detectar cambios en el archivo original, pregunta al usuario si guardar el
archivo bajo otro nombre.

:caution.Volver a editar el formulario guardado anteriormente har† que los
nuevos datos se almacenen con los antiguos, que no se eliminan del archivo.
Esto puede representar un riesgo de seguridad. Por este motivo se recomienda
encarecidamente guardar datos s¢lo en formularios PDF sin usar previamente, en
vez de simplemente reutilizar un formulario ya existente, cumplimentado total o
parcialmente, y editar los datos introducidos.:ecaution.

Otros tipos relacionados de documentos para manejar datos en formularios son
FDF (Forms Data Format) y XFDF (XML Forms Data Format). Actualmente
:hp2.Lucide:ehp2. no permite trabajar con ninguno de estos al no d†rseles
soporte en Poppler.

:p.Las versiones m†s recientes de Acrobat tambiÇn pueden emplear elementos
JavaScript en un documento PDF para cosas tales como listas desplegables y
otros datos de presentaci¢n condicional. Actualmente :hp2.Lucide:ehp2. no
reconoce estos tipos de campos, aunque puede mostrar fielmente el resto del
documento e incluso permitir introducir datos en los dem†s campos de los
formularios. Se recomienda no utilizar :hp2.Lucide:ehp2. para estos documentos.
Esta limitaci¢n puede abordarse en versiones futuras de la biblioteca Poppler.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=720.Formularios PDF:elink.
.br
:link reftype=hd res=219.Guardar...:elink.
.br
:link reftype=hd res=220.Guardar como...:elink.
.br
:link reftype=hd res=506.®C¢mo se... cumplimentan formularios PDF?:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
:edl.

.* ............................................................................
:h2 res=730 name=pdf_security
    x=left y=bottom width=100% height=100%.Seguridad PDF

El est†ndar PDF ofrece diversos tipos y niveles de seguridad en los
documentos de este tipo&colon.

:ul.
:li.Contrase§as cifradas
:li.Certificados de seguridad
:li.Encapsulado PDF seguro
:li.Permisos
:eul.

:p.Las contrase§as para abrir documentos PDF (generalmente conocidas como
contrase§a del propietario) se cifran actualmente con algoritmos :link
refid=rc4 reftype=fn.RC4:elink. de 10 o 128 bits (considerados dÇbiles seg£n
los est†ndares de hoy incluso en su variante de 128 bits) o, en los documentos
creados con versiones m†s recientes de Acrobat u otras herramientas, :link
refid=aes reftype=fn.AES:elink. de 128 o 256 bits.

:p.:hp2.Lucide:ehp2. es capaz de abrir documentos con ambos tipos de cifrado,
incluido el AES de 256 bits m†s reciente.

:hp2.
:table cols='30 15 15'.
:row.
:c.Revisi¢n de PDF (versi¢n de Acrobat)
:c.Algoritmo y longitud de cifrado
:c.Longitud m†xima de la contrase§a
:row.
:c.PDF 1.1 - 1.3 (Acrobat 2-4)
:c.RC4 40 bits
:c.32 caracteres (Lat°n-1)
:row.
:c.PDF 1.4 (Acrobat 5)
:c.RC4 128 bits
:c.32 caracteres (Lat°n-1)
:row.
:c.PDF 1.5 (Acrobat 6)
:c.RC4 128 bits
:c.32 caracteres (Lat°n-1)
:row.
:c.PDF 1.6 (Acrobat 7) y PDF 1.7 (ISO 32000-1) (Acrobat 8)
:c.AES-128
:c.32 caracteres (Lat°n-1)
:row.
:c.PDF 1.7 Adobe Extension Level 3 (Acrobat 9)
:c.AES-256
:c.127 bytes UTF-8 (Unicode)
:row.
:c.PDF 1.7 Adobe Extension Level 8 (Acrobat X/XI/DC) y (se espera) PDF
2.0 (especificaci¢n ISO 32000-2 por finalizar)
:c.AES-256
:c.127 bytes UTF-8 (Unicode)
:etable.
:ehp2.

:p.Se puede utilizar certificados digitales (elaborados por uno mismo o por
terceros fiables) para cifrar (con los mismos algoritmos disponibles para el
uso de contrase§as) o ÆfirmarØ documentos digitalmente. Dichas firmas digitales
se consideran legalmente vinculantes en muchas jurisdicciones.

:p.Actualmente, :hp2.Lucide:ehp2. no tiene forma de manejar los certificados de
seguridad, aunque los documentos firmados con un identificador (ID) digital se
pueden leer (y mostrar su firma y sello digitales) siempre que no hara sido
tambiÇn cifrado con un certificado.

:p.Los encapsulados o sobres PDF seguros son esencialmente grupos de archivos
encapsulados en (o m†s bien, adjuntados a) un archivo PDF que sirve como
contenedor (o p†gina de cubierta). Se puede entonces proteger el encapsulaado
mediante contrase§a y opcionalmente firmarlo y proteger con contrase§a tambiÇn
el contenido.

:p.Si el encapsulado no est† cifrado o est† protegido con contrase§a,
:hp2.Lucide:ehp2. podr† abrir el propio encapsulado PDF. Sin embargo, el
contenido, o archivos adjuntos &mdash.que pueden ser de cualquier tipo&mdash.
no ser†n accesibles.

:p.Los permisos incluyen restricciones a la impresi¢n y copia del contenido
(al portapapeles del sistema o guardando el documento en otro archivo), as°
como permitir acceso a lectores de pantalla, etc.

:p.Los permisos de un documento se establecen en el archivo PDF en el momento
de su creaci¢n y soslayar sus restricciones normalmente necesita una contrase§a
aparte. La biblioteca Poppler que :hp2.Lucide:ehp2. utiliza ignora tales
restricciones y no solicita que se introduzca la contrase§a para hacerlo.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=840.Seguridad:elink.
.br
:link reftype=hd res=710.Tipos de documentos PDF:elink.
.br
:link reftype=hd res=220.Guardar como...:elink.
:edl.

.* ............................................................................
:fn id=rc4.
RC4 (Cifrado Rivest 4), una vez conocido por su elegancia y velocidad, ha sido
relegado a la inutilidad como mÇtodo de cifrado fuerte. Es particularmente
vulnerable cuando no se descarta el inicio de la salida del flujo de datos de
las claves, o las claves utilizadas carecen de un nuivel suficente de entrop°a.
Se recomienda que no se utilicen los cifrados RC4 (ni siquiera de 128 bits) si
la seguridad constituye una verdadera preocupaci¢n.

:p.P†gina de Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/RC4
:efn.

.* ............................................................................
:fn id=aes.
AES (Advanced Encryption Standard), o Rijndael, desarrollado por los dos
cript¢grafos belgas Joan Daemen y Vincent Rijmen, fue adoptado por el Instituto
Nacional de Est†ndares y Tecnolog°a de Estados Unidos (NIST) en 2001 como FIPS
PUB 197 (FIPS 197).

:p.El NIST utiliza tres cifrados diferentes para el AES, cada uno con un tama§o
de bloque de 128 bits, pero con tres longitudes de clave diferentes (128, 192 y
256 bits).

:p.El algoritmo descrito por AES tiene simetr°a de clave (es decir, se utiliza
la misma clave para cifrar y descifrar los datos).

:p.En la actualidad AES se considera el mejor medio de encriptar datos para su
transmisi¢n en tr†nsito o en almacenamiento.

:p.P†gina de Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/Advanced_Encryption_Standard
:efn.

.* ............................................................................
:h2 res=740 name=pdf_hyperlinks
    x=left y=bottom width=100% height=100%.Enlaces PDF

Los enlaces en documentos PDF pueden llevar a otros puntos del mismo documento,
otros documentos o abrir programas externos (para mostrar contenido web o la
redactar correos).

:p.Para abrir adecuadamente hiperenlaces (a la web o redacci¢n de mensajes), es
necesario asegurarse de que las aplicaciones por omisi¢n para el Worplace
Shell de OS/2 se hayan configurado adecuadamente. :hp2.Lucide:ehp2. pasar† la
ubicaci¢n de destino del enlace a la aplicaci¢n configurada.

:p.Dependiendo del tipo de enlaces, :hp2.Lucide:ehp2. puede manejarlos o no
seg£n sus expectativas. Los enlaces internos de los documentos deber°an
funcionar, as° como los enlaces a Internet (consulte :link reftype=hd
res=510.Abrir enlaces:elink. para m†s detalles).

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=510.Abrir enlaces:elink.
.br
:link reftype=hd res=217.Èltimo enlace seguido:elink.
:edl.

.* ............................................................................
:h2 res=780 name=img_formats
    x=left y=bottom width=100% height=100%.Formatos de imagen

Los m¢dulos incluidos con :hp2.Lucide:ehp2. para manejar archivos de imagen
aceptan los siguientes tipos de archivos&colon.

:p.Gracias a la arquitectura modular de :hp2.Lucide:ehp2., es posible crear uno
o m†s m¢dulos nuevos para dar soporte a diversos formatos de archivo
adicionales o sustituir uno o m†s de los m¢dulos incluidos con otro m†s
robusto.

:p.El m¢dulo :link refid=gbm reftype=fn.GBM (Generalized Bitmap Module):elink.,
que es capaz de mostrar los formatos BMP, JPG, JP2, PNG, TIF, PBM, PGM, PPM,
PNM, XPM, JBG y RAW, ahora forma parte de :hp2.Lucide:ehp2.. Nuestro mayor
agradecimiento a Heiko Nitzsche, su desarrollador, por permitirnos incluirlo.
Deber°a utilizarse en sustituci¢n del m¢dulo JPG de :hp2.Lucide:ehp2..

:p.:hp2.Lucide:ehp2. utiliza DjVuLibre para su m¢dulo :link refid=djvu
reftype=fn.DjVu:elink.. Para :hp2.Lucide:ehp2., todos los archivos DjVu son
im†genes, incluso aunque contengan una capa de texto procedente de un OCR. Por
tanto, no se puede buscar en los documentos DjVu.

:p.El m¢dulo :link refid=jpeg reftype=fn.JPEG:elink. (JPG) no deber°a
instalarse con el m¢dulo GBM, que tambiÇn soporta JPG. Por omisi¢n, el m¢dulo
JPG no se instala con la versi¢n 1.5.0. Se instalaba con las anteriores,
sin embargo, de modo que deber°a desinstalar las versiones previas antes de
instalar la 1.5.0 (recomendado) o borrar o renombrar lujpeg.dll.

:dl tsize=10 break=none.
:dt.:hp2.Relacionado&colon.:ehp2.
:dd.:link reftype=hd res=900.Referencias:elink.
.br
:link reftype=hd res=580.Problemas:elink.
.br
:link reftype=hd res=582.Nuevas funciones:elink.
:edl.

.* ............................................................................
:fn id=jpeg.
Acr¢nimo del Grupo Conjunto de Expertos en Fotograf°a (Joint Photographic
Experts Group), que cre¢ el formato, JPEG (tambiÇn conocido por su extensi¢n de
archivo com£n, ÆJPGØ) ofrece compresi¢n con pÇrdida ajustable para im†genes
digitales y es particularmente id¢neo para la fotograf°a digital. Normalmente,
JPEG puede lograr compresiones de 10&colon.1 antes de que se produzcan pÇrdidas
de calidad de la imagen apreciables (a simple vista).

:p.Existen muchas variantes de JPEG, la m†s com£n de las cuales actualmente
es JPEG/Exif, ya que la utilizan las c†maras digitales y otros dispositivos de
captura de imagen, aunque normalmente todas las variantes se denominan JPEG.

:p.P†gina de Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/JPEG
:efn.

.* ............................................................................
:fn id=gbm.
GBM (Generalized Bitmap Module) es una biblioteca de manejo de muchos formatos
diferentes de im†genes de tipo mapa de bits. Incluye un £til conjunto de
herramientas para manipular mapas de bits y convertir formatos. En esta versi¢n
se incluye adicionalmente soporte para BMP, JPG, JP2, PNG, TIF, PBM, PGM, PPM,
PNM, XPM, JBG y RAW.

:p.El paquete completo se encuentra en Hobbes&colon.
http&colon.//hobbes.nmsu.edu/h-search.php?key=gbmos2pm160_gbm176_lu143_moz147_bin_wpi

:p.P†gina en Internet&colon.
.br
http&colon.//heikon.home.tlink.de/frames/gbm_plugin_lucide.html
:efn.

.* ............................................................................
:fn id=djvu.
Desarrollado originalmente por Yann LeCun, LÇon Bottou, Patrick Haffner y Paul
G. Howard en AT&amp.T Labs entre 1996 y 2001, DjVu es una tÇcnica de compresi¢n
y formato para archivado de documentos espec°ficamente dise§ado para
bibliotecas digitales de originales impresos, digitalizados o producidos
digitalmente. Para los originales digitalizados, los archivos DjVu son
t°picamente de 3 a 10 veces m†s peque§os que los TIFF o PDF en blanco y negro y
de 5 a 10 veces m†s peque§os que los JPEGs a color de resoluciones similares.

:p.Los archivos DjVu pueden contener una capa de texto OCR, en la que se hayan
almacenado los caracteres textuales reconocidos en las im†genes. Algunos
visores permitern explora y copiar dicho texto.

:p.Debido a sus tama§os menores comparados con PDF, los archivos DjVu son
particularmente id¢neos para distribuir archivos por web, especialmente por
conexiones de bajo ancho de banda.

:p.P†gina en Wikipedia&colon.
.br
https&colon.//en.wikipedia.org/wiki/DjVu
:efn.

.* ............................................................................
:h1 res=800 name=approach
    x=left y=bottom width=100% height=100%.Enfoque

La arquitectura modular de :hp2.Lucide:ehp2. ofrece un entorno estructurado para
a§adir soporte de nuevos formatos de archivo, y la arquitectura basada en SOM
de sus m¢dulos hace que Çstos sean f†ciles de desarrollar para programadores
de terceras partes.

:p.Esta secci¢n del manual del usuario repasa la filosof°a de dise§o de
:hp2.Lucide:ehp2. y c¢mo encajan todas las partes.

:ul compact.
:li.:link reftype=hd res=820.Arquitectura modular:elink.
:li.:link reftype=hd res=830.M¢dulos incluidos:elink.
:li.:link reftype=hd res=840.Seguridad:elink.
:eul.

.* ............................................................................
:h2 res=820 name=plugin_architecture
    x=left y=bottom width=100% height=100%.Arquitectura modular

La aqrquitectura modular de :hp2.Lucide:ehp2. utiliza SOM (System Object Model)
para facilitar el desarrollo de nuevos m¢dulos para ampliar las capacidades de
:hp2.Lucide:ehp2..

:p.Se pueden crear m¢dulos a partir de fuentes diversas para que
:hp2.Lucide:ehp2. los cargue al iniciarse. Todas las funciones configuradas en
el m¢dulo pasan a estar disponibles para :hp2.Lucide:ehp2., incluyendo los
detalles de la informaci¢n que se puede mostrar sobre el archivo y la
posibilidad de realizar b£squedas.

:p.Se puede solicitar la creaci¢n de nuevos m¢dulos a travÇs de la p†gina del
proyecto :hp2.Lucide:ehp2.&colon.
.br
https&colon.//trac.netlabs.org/lucide/
.br
o cualquier tercero capaz puede desarrollarlos de forma completamente
independiente del propio :hp2.Lucide:ehp2..

:p.La licencia dual de :hp2.Lucide:ehp2. tambiÇn permite el desarrollo
comercial de m¢dulos.

.* ............................................................................
:h2 res=830 name=included_plugins
    x=left y=bottom width=100% height=100%.M¢dulos incluidos

Con :hp2.Lucide:ehp2. se incluyen m¢dulos para ver documentos PDF, DjVu y un
amplio abanico de formatos de imagen utilizando el m¢dulo GBM. Aunque a£n
se incluye un m¢dulo para ver im†genes JPG, recomendamos que instale el m¢dulo
GBM, que da soporte a JPG, y no instale o desinstale el m¢dulo JPG, ya que
hemos observado problemas al abrir archivos cuando hay instalados dos m¢dulos
que manejan el mismo formato.

:p.Para m†s informaci¢n sobre los m¢dulos disponibles, consulte :link
reftype=hd res=780.Formatos de imagen:elink..

.* ............................................................................
:h2 res=840 name=security
    x=left y=bottom width=100% height=100%.Seguridad

El proyecto :hp2.Lucide:ehp2. se toma en serio la seguridad documental. La
desactivaci¢n autom†tica de la creaci¢n de miniaturas para los documentos
protegidos y la capacidad de inhabilitar completamente la creaci¢n de las
mismas por omisi¢n son dos ejemplos de este compromiso con la seguridad del
usuario.

:p.:hp2.Lucide:ehp2. no almacena contrase§as u otra informaci¢n personal sobre
el usuario, ni cachea metadatos de ninguna clase de los documentos abiertos o
examinados. Las miniaturas, cuando se crean, est†n completamente desvinculadas
de :hp2.Lucide:ehp2. y se pueden borrar en cualquier momento.

:p.:hp2.Lucide:ehp2. no dispone de herramientas para retirar contrase§as de los
archivos protegidos.

:p.Si le preocupa su privacidad o seguridad, por favor abra una incidencia en
la p†gina del proyecto :hp2.Lucide:ehp2.&colon.
.br
https&colon.//trac.netlabs.org/lucide/

.* ............................................................................
:h1 res=880 name=env_vars
x=left y=bottom width=100% height=100%.Variables de entorno

:hp2.Lucide:ehp2. busca las siguiente variables de entorno al iniciarse:

:ul compact.
:li.:hp2.LUCIDEINSTALLPATH:ehp2. indica a :hp2.Lucide:ehp2. d¢nde
encontrar sus archivos.
:li.:hp2.LUCIDEHELP:ehp2. es una lista concatenada de archivos de ayuda,
empezando por el propio archivo de ayuda de :hp2.Lucide:ehp2., que se abrir†n
al invocar al sistema de ayuda desde el propio programa. Los m¢dulos deber°an
anexar sus propios archivos de ayuda a esta lista (mediante Æ+Ø).
:eul.

:p.Si estas variables no existen en CONFIG.SYS en el momento de la instalaci¢n,
se crear†n. Si ya existen, se respetar†n.

.* ............................................................................
:h1 res=900 name=refs
    x=left y=bottom width=100% height=100%.Referencias

Los siguientes enlaces deber°an proporcionar un punto de arranque para
informarse m†s sobre :hp2.Lucide:ehp2.&colon.

:nt.Algunos enlaces pueden no estar disponibles en todos los sistemas.:ent.

:ul compact.
:li.Wiki de :hp2.Lucide:ehp2.&colon. https&colon.//trac.netlabs.org/lucide/
:p.
:hp2.PDF&colon.:ehp2.
:li.3DPDF Consortium&colon. http&colon.//www.3dpdfconsortium.org/
:li.Adobe Systems Incorporated&colon. https&colon.//www.adobe.com
:li.PDF Association&colon. http&colon.//www.pdfa.org/
:li.PDFlib knowledge base&colon.
https&colon.//www.pdflib.com/en/knowledge-base/
:li.Proyecto Poppler&colon. https&colon.//poppler.freedesktop.org/
:li.Fallos en Poppler (abiertos)&colon.
https&colon.//bugs.freedesktop.org/buglist.cgi?bug_status=__open__&amp.no_redirect=1&amp.order=Importance&amp.product=poppler&amp.query_format=specific
:p.
:hp2.DjVu&colon.:ehp2.
:li.DjVuLibre&colon. https&colon.//djvu.sourceforge.net/index.html
:li.DjVu.org&colon. http&colon.//www.djvu.org/
:li.DjVu.com&colon. http&colon.//djvu.com/
:p.
:hp2.JPEG y otros formatos de imagen&colon.:ehp2.
:li.Grupo Independiente JPEG http&colon.//www.ijg.org/files/
:li.Generalized Bitmap Module&colon.
http&colon.//heikon.home.tlink.de/frames/gbm_plugin_lucide.html
:p.
:hp2.General&colon.:ehp2.
:li.Archivo Hobbes&colon. http&colon.//hobbes.nmsu.edu/
:li.International Organization for Standardization (ISO)&colon.
http&colon.//www.iso.org/iso/home.htm
:li.ECMA International&colon.
http&colon.//www.ecma-international.org/
:eul.

.* ............................................................................
:h1 res=950 name=notices
    x=left y=bottom width=100% height=100%.Avisos

Copyright ∏ 2016 netlabs.org en colaboraci¢n con Arca Noae, LLC;
.br
anteriormente Copyright ∏ Eugene Romanenko, Dmitriy Kuminov, Silvan Scherrer,
bww bitwise works GmbH en colaboraci¢n con Mensys B.V., Pa°ses Bajos.

:p.Otros derechos de copia pertenecen a sus respectivos propietarios.

.* ............................................................................
:h1 res=960 name=appendix
    x=left y=bottom width=100% height=100%.ApÇndice

Los m¢dulos que incluyan su propia ayuda aparecer†n tras esta p†gina y deber°an
listarse en el °ndice de contenido de esta gu°a.

:euserdoc.
