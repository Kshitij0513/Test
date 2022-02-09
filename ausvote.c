#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { false=0, true } bool;

#define CANDIDATE_MAX_NUM_CHARS 80
#define MAX_NUM_CANDIDATES 20
#define MAX_NUM_VOTERS 1000

typedef struct {
char name[CANDIDATE_MAX_NUM_CHARS+1];
bool eliminated;
} Candidate;

typedef struct {
unsigned int choices[MAX_NUM_CANDIDATES];
unsigned int currentChoice;
} Voter;

int main(int argc, char **argv) {
unsigned int numCases, caseNum;
unsigned int numCandidates, candidateNum;
Candidate candidates[MAX_NUM_CANDIDATES];
Voter voters[MAX_NUM_VOTERS];
unsigned int numVoters, voterNum;
unsigned int choiceNum;
unsigned numVotes[MAX_NUM_CANDIDATES];
unsigned int minNumVotes;
unsigned int numVotesRequiredToWin;
bool finished;
bool knowNumVotes;
bool areAllTied;
unsigned int misc;

char *cp;
char buf[256];

scanf("%u\n", &numCases);
for (caseNum=0; caseNum<numCases; caseNum++) {
memset(candidates, 0, sizeof(candidates));
memset(voters, 0, sizeof(voters));

scanf("%u\n", &numCandidates);
for (candidateNum=0; candidateNum<numCandidates; candidateNum++) {
fgets(candidates[candidateNum].name, sizeof(candidates[candidateNum].name), stdin);
cp = strchr(candidates[candidateNum].name, '\n');
if (*cp) *cp = '\0';
}

for (voterNum=0; voterNum<MAX_NUM_VOTERS; voterNum++) {
fgets(buf, sizeof(buf), stdin);
if (strlen(buf) == 1) break;

for (cp=strtok(buf, " \n"), choiceNum=0; cp; cp=strtok(NULL, " \n"), choiceNum++) {
voters[voterNum].choices[choiceNum] = atoi(cp) - 1;
}
}
numVoters = voterNum;

numVotesRequiredToWin = numVoters / 2 + 1;

/* candidate and voter data is read in at this point */

finished = false;

memset(numVotes, 0, sizeof(numVotes));

/* initial count */
for (voterNum=0; voterNum<numVoters; voterNum++) {
numVotes[voters[voterNum].choices[voters[voterNum].currentChoice]]++;
}

while (1) {
for (candidateNum=0; candidateNum<numCandidates; candidateNum++) {
if (!candidates[candidateNum].eliminated && numVotes[candidateNum] >= numVotesRequiredToWin) {
if (caseNum > 0) putchar('\n');
puts(candidates[candidateNum].name);

finished = true;
break;
}
}
if (finished) break;

/* check for tied condition */
knowNumVotes = false;
areAllTied = true;
for (candidateNum=0; candidateNum<numCandidates; candidateNum++) {
if (!candidates[candidateNum].eliminated) {
if (!knowNumVotes) {
misc = numVotes[candidateNum];
knowNumVotes = true;
continue;
}

if (numVotes[candidateNum] != misc) {
areAllTied = false;
break;
}
}
}

if (areAllTied) {
if (caseNum > 0) putchar('\n');
for (candidateNum=0; candidateNum<numCandidates; candidateNum++) {
if (!candidates[candidateNum].eliminated) {
puts(candidates[candidateNum].name);
}
}

break;
}

/* determine the lowest number of votes anyone got */
minNumVotes = 0xffffffff;
for (candidateNum=0; candidateNum<numCandidates; candidateNum++) {
if (!candidates[candidateNum].eliminated && numVotes[candidateNum] < minNumVotes) {
minNumVotes = numVotes[candidateNum];
}
}

/* eliminate candidates who got that number of votes and adjust the voters */
for (candidateNum=0; candidateNum<numCandidates; candidateNum++) {
if (!candidates[candidateNum].eliminated && numVotes[candidateNum] == minNumVotes) {
candidates[candidateNum].eliminated = true;

/* adjust voters who voted for that guy */
for (voterNum=0; voterNum<numVoters; voterNum++) {
if (voters[voterNum].choices[voters[voterNum].currentChoice] == candidateNum) {
do {
voters[voterNum].currentChoice++;
} while (candidates[voters[voterNum].currentChoice].eliminated);

/* recount that vote for the next best candidate */
numVotes[voters[voterNum].choices[voters[voterNum].currentChoice]]++;
}
}
}
}
}
}

return 0;
}
