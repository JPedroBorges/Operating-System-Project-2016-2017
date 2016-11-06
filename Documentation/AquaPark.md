# Simulator
	simulation time: 12h
	max people simulated: 267785

# AquaPark
	Hours: 8h – 20h
		People come and go as they please
	maximum capacity: 10 000 people
		At same time
	Queue: 10


# Attractions:
## Swimming pool
	Duration: variable
	Ride: Max(100) at time
		starts: always running
	Queue: 100
		Priority: VIP
		Age: Free
## A Ovelha Choné Swimming pool
	Duration: variable
	Ride: Max(100) at time
		starts: always running
	Queue: 5
		Priority: VIP
	Age: Under 12
## diving platform
	Duration: 1 - 5 seconds
	Ride: 1  at time
		starts: after 1 person is ready && 5 after last time
	Queue: 100
		Priority: VIP
		Priority: older people
	Age: Over 12
## Toboggan
	Duration: 25 seconds
	Ride: 1 || 2  at time
		Starts: when 1 or 2 people are ready && 25 after last time
	Queue: 100
		Priority: VIP
		Priority: 2 people at same time
	Age: Over 12
## Toboggan XXX
	Duration: 25 seconds
	Ride: 2 || 4  at time
		Starts: when 2 or 4 people are ready && 25 after last time
	Queue: 100
		Priority: VIP
		Priority: couples first
	Age: Over 18
## Toboggan Race
	Duration: 10 - 15 seconds
	Ride: 1 - 4
		starts: every 20sec
	Queue: 100
		Priority: VIP
		Priority: couples first
	Age: Over 18
## Slow river
	Duration: 300 seconds
	Ride: 1 || 2 || 4  at time
		Starts: when 2 or 4 people
	Queue: 100
		Priority: VIP
		Priority: VIP
	Age: free
## Sunbath
	Duration: variable
	Ride: Max(10 000)  at time
		starts: always running
	Queue: Instant access
	Age:  free
## walking
	Duration: variable
	Ride: Max(10 000)  at time
		starts: always running
	Queue: Instant access
	Age: free

# Person:
	VIP:0 - 10%
	Age: 0 - 122
	coupled with: other person
	time on park: 0 - 12h
	maximum waiting time: 0 - 600 seconds

# Entrance type:
	Family:
		Number of people: > 2
			at least 1 person over 18
	Couple:
		Number of people: 2
			people over 18
	simgle:
		number of people: 1
			person over 18

# Rules:
	A person has to walk from attraction to attraction
	couples stick together all the time
