/* 
 * Convert 'SOMEXTERN {' to 'SOMEXTERNF {' 
 *
 * Usage:
 *    cnvsomex <filename.xh>
 */

parse arg f
tmp = "tmp.tmp"

do while lines(f)
	l=linein(f)
	if l="SOMEXTERN {" then l="SOMEXTERNF {"
	call lineout tmp, l
end	

call lineout f
call lineout tmp

"@del "||f
"@ren "||tmp||" "||f
