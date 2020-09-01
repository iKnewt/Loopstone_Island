# Loopstone Island
Unreal Engine (4.24) Project for a game called Loopstone Island.
<br>[You can play the game here if you like](https://iknewt.itch.io/loopstone-island) 
<br>This repository will focus on the technial aspects of the project
<br>[You find the project's source code in the Source folder](/Source/Loopstone_Island/).

## Creators and credits
#### Project creators
>[Susanne Gjersund](https://github.com/iKnewt) (programmer)
<br>[Even Sigurdsson Bjørke Haaland](https://github.com/EvanHaal) (artist)
<br>[Martin Skalstad Steen](https://github.com/martinGFA) (programmer)
#### Full credits
>__Concept and project__ Martin, Even & Susanne
<br>__Story and script__ Martin
<br>__3D assets, textures, animations__ Even 
<br>__2D art__ Susanne
<br>__Code__ Susanne & Martin
<br>__Sound Effects__ Even & Martin
<br>__Music__ by [LAMØY](https://soundcloud.com/lamoymusic)
 
## Excerpt from report about the game production
Using Unreal Engine means a lot of the generally needed systems for games are already
implemented into the core game engine. Our biggest task was to sort out the functionality we
needed, finetune it to fit our game as well as developing any additional systems. Our team
consists of two programmers, and since our game does not require the most complex additional
systems we wanted to make sure everything developed for it was created by us from scratch.

### Conditional World Changes
As a game based on exploration, Loopstone Island changes during gameplay depending on the
actions of the player. Based on what the player does, there will be different dialogue options
available, different objects can be interacted with, different doors unlock and certain objects
become visible or hidden.

The primary conditions that change the map is what story and time of day is currently active.
Shortly summarized the morning is always the same and is where the player selects what story to
play the rest of the day. The rest of the day is different in content depending on what the player
chose, ending in the player finding a loopstone and either waking up in bed to restart the day, or
in case of the last loopstone, continuing to play past the point the story was interrupted. In
addition there are secondary conditions more connected to what the player has done, which we
have divided into events that have happened, topics that have been talked about and items the
player has in their inventory.

#### Keeping track of data
In order to have this functionality, we created a custom `Loopstone_IslandGameState` to
keep track of all the relevant actions the player did that would change the game. The code below 
shows how we used enums to keep track of current states, our primary conditions.

```cpp
GameStateEnums.h

UENUM (BlueprintType)
enum class ETimeOfDay : uint8
{
  Morning,
  Afternoon,
  Evening,
  Night,
  None
};

UENUM(BlueprintType)
enum class EStory : uint8
{
  Detective,
  PartyPlanner,
  AssistantChef,
  Psychologist,
  None
};
```
```cpp
Loopstone_IslandGameState.h

UPROPERTY(EditDefaultsOnly, Category = "Current Conditions" )
ETimeOfDay CurrentTimeOfDay = ETimeOfDay::Morning;

UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "CurrentConditions" )
EStory CurrentStory = EStory::None;
```

We used a similar setup for secondary conditions, but the enums are used to indicate indexes in a
corresponding array of bools, as seen in the code below. Originally, we wanted to create a more
complex condition system, since a system as simple as the one we ended with would quickly
become difficult to use since it relies on lists, and if the lists become too long they are hard to
navigate. Our game is too small for this to be an issue, so in the end we settled on the simplest
system due to time limitations. Later, we will get into the details on some methods we tried and
why we ultimately abandoned them.

```cpp
GameStateEnums.h

UENUM(BlueprintType)
enum class EInventoryItem : uint8
{
  Knife,
  Rope,
  Tape,
  KeyLighthouse,
  KeyBoathouse,
  Mushroom,
  Carrot,
  Foxglove,
  None
};

UENUM(BlueprintType)
enum class EEventType : uint8
{
  HasMachine,
  TutorialCompleted,
  DoctorWalkingAway,
  PartyPlannerCompleted,
  ChildDied,
  None
};

UENUM(BlueprintType)
enum class ETopic : uint8
{
  PartyPlanner,
  Tape,
  Rope,
  Knife,
  FarmerTalkedAboutInnkeeper,
  TalkedToFarmerAboutNoise,
  TalkedToDoctorAboutNoise,
  TalkedToMotherAboutNoise,
  TalkedToChildAboutNoise,
  TalkedToSBAboutNoise,
  HeardFarmersOpinionOnDoctor,
  TalkedToSBAboutRope,
  AskedChildAboutKey,
  TalkedToChildAboutSBDeath,
  TalkedToMotherAboutSBDeath,
  TalkedToFarmerAboutSBDeath,
  TalkedToInnkeeperAboutSBDeath,
  TalkedToDoctorABoutSBDeath,
  PartyReady,
  TalkedToDoctorAboutFeast,
  TalkedToFarmerAboutFeast,
  TalkedToMotherAboutFeast,
  TalkedToMotherAboutChildCondition,
  TalkedToChildAboutChildCondition,
  TalkedToDoctorAboutChildCondition,
  TalkedToMotherAboutDoctorOpinion,
  TalkedToDoctorAboutMotherOpinion,
  TalkedToSBAboutChildCondition,
  TalkedToDoctorAboutSBOpinion,
  TalkedToMotherAboutHelping,
  GivenMotherFoxGlove,
  TalkedToDoctorAboutFoxglove,
  TalkedToMotherAboutChildBeingDead,
  None
};
```
```cpp
Loopstone_IslandGameState.h

TArray< bool > bEventHasBeenTriggered;
TArray< bool > bTopicHasBeenRevealed;
TArray< bool > bInventoryItemsCollected;
```
A GameState is generally used for this purpose, tracking the state of the game at any given point.
The GameState in UE4 is reconstructed when a map is loaded, meaning the data cannot be
transferred between maps. This worked perfectly for our game, since we chose to do everything
within one map and rather set up conditions to decide what dialogue or objects were visible
instead of loading different maps. When the player goes to bed we simply reload the map,
resetting all the data as if nothing had happened. There is however some data we do need to keep
track of between maps, what loopstones the player has collected, so their overall progress can be
tracked and the loopstone can displayed in the machine. Since we wanted this data to be saved
even if the player closed the game and resumed at a later point, we simply stored this data in a
save game every time the player collects a loopstone (or the machine in the tutorial), and load the
data to the `Loopstone_IslandGameState` when it is created.

IMAGE

#### Changing data
In addition to this, the `Loopstone_IslandGameState` also holds a lot of pointers to different
objects on the map, as well as the widgets that change based on conditions. We did this so we
could use the GameState to hold the functionality connected with changes based on condition, no
matter if it was an object, dialogue or the player triggering that change they would all have
access to the GameState. Most physical changes to the game happen when the time of day shifts,
as can be seen in the code below. This code also shows how the different objects individually
keep the functions that actually change their behaviour, but we rely on the
`Loopstone_IslandGameState` to keep pointers to these objects so we can trigger the changes
when we want.

```cpp
Loopstone_IslandGameState.cpp

void ALoopstone_IslandGameState::ChangeTimeOfDay(ETimeOfDay NewTimeOfDay)
{
  CurrentTimeOfDay = NewTimeOfDay;
  
  // Change the sun and sky
  if (SunSky)
  {
    SunSky->ChangeTimeOfDay(NewTimeOfDay);
  }
  
  // Move islanders to position
  if (IsValid(TargetPointController))
  {
    TargetPointController->MoveIslandersToPosition(NewTimeOfDay, CurrentStory);
  }
  
  // Change sound effects and music
  for (auto Actor : SoundActors)
  {
    if (IsValid(Actor))
    {
      Actor->ChangeCurrentTimeOfDay(NewTimeOfDay);
    }
  }
  
  // Show certain Story-based items
  for (auto Actor : StoryDecorActors)
  {
    if (Actor)
    {
      Actor->UnhideIfConditionsMet(NewTimeOfDay, CurrentStory);
    }
  }
}
```

In future development, since the systems are already in place, we would add more such
conditional changes to the game to make it more rewarding to explore. Another thing we would
have liked to include which was commented on by playtesters is having the islanders walk to
their new positions instead of simply teleporting as they do now. This could have been done
either using AI or predetermined paths, and would also require some time to set up, which is why
we ended up abandoning the idea as it would not change the game much.

IMAGE

### Interactable Objects
Even though the major changes happen when the day of time changes, there are also other
smaller changes happening instantaneously based on the player's actions. The image above
shows the way conditions are set up within any children of the `InteractableObjectBase`,
where any conditions listed must be met in order for the player to successfully interact with the
object. The image specifically shows a `BP_Interactable_Foxglove`, which is a story
specific item that can be picked up once the player learns about it. On the right side we also see
how under Event this object triggers changing the inventory bool for Foxglove to true. Both of
these work by communicating with the `Loopstone_IslandGameState`, using the functions
shown below.

```cpp
Loopstone_IslandGameState.h

bool AreConditionsMet (TMap<ETopic, bool > TopicBoolsConditions,
                      TMap<EEventType, bool > EventBoolsConditions,
                      TMap<EInventoryItem, bool > IventoryBoolsConditions,
                      ETimeOfDay TimeOfDayCondition = ETimeOfDay::None,
                      EStory ActiveStoryCondition = EStory::None);

void ChangeConditions (TMap<ETopic, bool > TopicBoolsToChange,
                      TMap<EEventType, bool > EventBoolsToChange,
                      TMap<EInventoryItem, bool > IventoryBoolsChange,
                      ETimeOfDay TimeOfDayChange = ETimeOfDay::None,
                      EStory ActiveStoryChange = EStory::None) ;
```

IMAGE
IMAGE

The `Loopstone_IslandGameState` then handles the event. For the foxglove we send a signal
to the inventory widget to update and make the corresponding item's icon visible. The
`InteractableObjectBase`'s functions `virtual void Interact();` and `virtual void
DoNotInteract();` handles any local changes to the object, for the foxglove hiding it and
turning off collision.


We use a pulsing glow to indicate what objects are interactable to the player. This is set to trigger
on any object the player looks at that is marked interactable regardless of whether its conditions
are met or not. In future development we would look into a way to control this, so that for
example doors could glow regardless, since they can indicate that they are locked, while other
objects could glow only when the player can actually interact with them.

IMAGE

### Dialogue System
Our game's core game mechanic is talking to characters, and so its biggest system is the dialogue
system we created especially for this game. Based on the concept we knew early on we would
need a solid dialogue system, but this is also one of the reasons we chose the concept, for the
challenge of developing such a system from the bottom up.


Since the story and dialogue is not linear but based on player interactions and the current
conditions of the world, we focused on creating a system that could visualize the relationships
between different dialogue as well as being as easy to use and intuitive as possible. After
researching and testing out different solutions, we decided on creating a custom Graph Editor for
_Unreal Engine_. We chose to add jinyuliao's _GenericGraphPlugin_ (2016) to our project, a plugin
that would handle the communication between our code and the _Unreal Editor_, as creating such
a system ourselves would require a lot of experience with Plugin writing for _Unreal Engine_
which we did not have time for. Luckily this plugin did not contain anything outside this
communication, meaning we still got to develop our own system from scratch, which was perfect
as graph structures were part of our education, but now we had a way to view and edit its data
visually. We made sure to study the plugin so we knew how all its parts worked.

IMAGE

The image shows how nodes and edges are displayed in the editor, also making it clear that this
is a directional graph. In our system nodes represent dialogue from a character, and the edges are
responses from the player. The graph supports using any number of node types, but to keep
things simple we decided to stick with one node type, and rather use enums to define its
functionality. This was mostly since we could not know exactly what data and functionality we
would need until we were actively using the system, and we needed to start using it as quickly as
possible. Each node contains very little data so we do not think this is a problem for our small
game. The only functional difference between our nodes are how they handle and show their
edges/ player responses in the dialogue UI. As seen in the image, the nodes are color coded
based on this for easy readability. "No Options" simply means the player could just click to see
the next dialogue, useful for breaking up long dialogue. "Options" is used when the player
responds to dialogue while "Options with Exit" is used as a dialogue Hub, often used to let the
player ask optional questions to a character.


All nodes and edges use conditions in the exact same way as interactive objects do to determine
if they should be shown or not during conversations. This was fairly easy to set up as this
functionality lies in the `Loopstone_IslandGameState`, which also handles the
communication between the various dialogue graphs and dialogue widget. The nodes can also
change conditions and trigger events, which can be seen in the game when Jude removed the
foxglove from the inventory during conversation.

IMAGE

In addition, the nodes allow for easy highlighting of key information in dialogue text as seen in
the picture above. Based on feedback from playtesters we also added functionality to Display
different text if the node had already been visited before, making the dialogue more natural and
by extension the characters more realistic.

IMAGE

Finally, each node lets us set the Expression and Animation of the character speaking. With this
system it became easier to create full dialogues as you could visualize the dialogue text,
associated emotion and all connected options and dialogue paths in one big graph.
