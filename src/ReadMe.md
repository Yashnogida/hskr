
Default note placement is a quarter note

Mousing over note selects it briefly

Scrolling up on a note changes its time count

Drag to select multiple notes


Steps for the permutation algorithm:

    (1) Identify patterns. If any pattern are intentionally selected, group them as a pattern. For the remaining notes that aren't selected, group them into a patterns based on the maximum consecutive hits rule.
    
    (2) Permutate:
            Collect the number of individual symbols in the pattern. For patterns with groups, any groups are considered one symbol, and the remaining notes or groups of notes are considered a symbol based on the rule setting. 
            
            The number of permutations is:
                (MAX # of distinct symbols) raised to the (# of fastest beats in the bar).
                
    while discarding any of the patterns that come across a rule where 

    (3) Treat rests as a "wildcard" for allowing a rule violation. 
    