/* Simplest unix install command replacement for kBuild */
/* (built-in install strips EAs which in particular kills file icons) */
'@echo off'
parse arg '--' from to
'copy' translate(from, '\', '/') translate(to, '\', '/')

