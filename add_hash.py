import sys
import os
import re

with open(sys.argv[1], 'r') as f:
    s = f.read()

idx = s.find(r'\subsection{', 0)
while idx != -1:
    start_idx, end_idx = idx, s.find('}', idx)
    file_start_idx = s.find(r'\lstinputlisting{', end_idx) + 17
    file_end_idx = s.find('}', file_start_idx)
    file_name = s[file_start_idx:file_end_idx]
    if os.path.isfile(file_name) and file_name.endswith('cpp'):
        hashval = os.popen('./hash.sh {}'.format(file_name)).read().strip()
        s = s[:start_idx] + s[start_idx:end_idx] + ' ' + hashval + s[end_idx:]
    idx = s.find(r'\subsection{', file_end_idx)

with open(sys.argv[2], 'w') as f:
    print(s, file=f)
