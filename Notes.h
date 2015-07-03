/* 
 * File:   Notes.h
 * Author: Jahan
 *
 * 
 * I CNF formula - A conjunction of some clauses: (a ∨ b¯ ∨ c) ∧ (¯c ∨ ¯a)
A formula is satisfied by a variable assignment if every clause has at least one
literal which is true under that assignment.
A formula is unsatisfied by a variable assignment if some clause’s literals are all
false under that assignment
 * 
 * 
 * I Periodically restart the search while keeping some learned clauses
I Try to avoid “dead ends” where heuristics are pushing in the wrong direction
I Most solvers increase limitations on backtracks and learned clauses at each
restart

 * 
 * To prune branches where a = false, b = true, c = true, add conflict clause
a b¯ c¯.
I Pruning is implicit in BCP.
I Use learned clause to determine how far to backtrack.
I Backtrack to earliest decision level in which exactly one variable is unassigned.
I How to calculate this clause?

 * 
 * Created on 3 juillet 2015, 16:56
 */

#ifndef NOTES_H
#define	NOTES_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* NOTES_H */

