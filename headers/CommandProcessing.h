#ifndef COMMAND_PROCESSING_H
#define COMMAND_PROCESSING_H

//  Compiler specific macros
//  Disables clang modernize suggestions
#ifdef __GNUC__
#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#endif

#include <string>
#include <vector>
#include <iostream>
#include <queue>



//  Forward declaration of required classes from other header files. (included in .cpp file)
class State;                //  GameEngine.cpp
class TransitionData;       //  GameEngine.cpp
class GameEngine;           //  GameEngine.cpp



/** \class Command
 *  \brief Class that encapsulates a command, storing additional information and providing helpful methods. */
class Command {
public:
    //  Constructors/Destructor
    /** \brief Constructs a Command object with default values. */
    Command();
    /** \brief Constructs a Command object with a given raw command string. */
    explicit Command(const std::string&);
    /** \brief Constructs a Command object with the given values. */
    Command(const std::string&, std::string , const bool*);
    /** \brief Constructs a Command object from another Command object. */
    Command(const Command&);
    /** \brief Deconstructs a Command object. */
    ~Command();


    //  Operator overrides
    /** \brief Assigns values from another Command object to the current object. */
    Command& operator=(const Command&);
    /** \brief Stream insertion operator override, outputs non-null values. */
    friend std::ostream& operator<<(std::ostream&, const Command&);


    //  Getter/Accessor methods
    /** \brief Gets the raw command. */
    std::string getRawCommand() const;
    /** \brief Gets the effect of command execution, if executed. */
    std::string getEffect() const;
    /** \brief Returns a pointer to a boolean variable indicating whether or not execution was successful or not.
     *  \remarks A 'nullptr' indicates that the command has not been executed yet. */
    const bool* getIsValidExecution() const;


    //  Setter/Mutator methods
    /** \brief Updates the raw command. */
    void setRawCommand(const std::string&);
    /** \brief Updates the effect. */
    void setEffect(const std::string&);
    /** \brief Sets the execution status of the command. */
    void setExecutionStatus(bool);


    //  Other methods
    /** \brief Returns the first token in the raw command string. */
    std::string getFirstToken() const;
    /** \brief Returns a vector containing the remaining tokens from the raw command string.
     * Returns a string list (//vector) containing every token but the first. */
    std::vector<std::string> getRemainingTokens() const;
    /** \brief Returns the number of arguments. */
    size_t getNumberOfArguments() const;

private:
    //  The raw command, as read from an input stream.
    std::string rawCommand;

    //  The effect message, or execution message. Could be an error or success message.
    std::string effect;

    //  Boolean on whether the command executed properly.
    bool* isValidExecution;

    //  A vector of tokens.
    std::vector<std::string> tokens;
};



/** \class CommandProcessor
 *  \brief Abstract class representing a source of pre-processed commands.
 *  \remarks Note that commands returned are syntactically valid, however, they may still be erroneous in a specific
 *  context (ex. command to attack a player that does not exist). Error handling for those types of exceptions are
 *  delegated to the caller or the client. */
class CommandProcessor {
public:
    //  Constructors/Deconstructor
    /** \brief Constructs a default CommandProcessor object. */
    CommandProcessor();
    /** \brief Constructs a CommandProcessor object. */
    CommandProcessor(std::vector<State>, std::vector<TransitionData>);
    /** \brief Constructs a CommandProcessor object using data from a GameEngine object. */
    explicit CommandProcessor(const GameEngine&);
    /** \brief Deconstructs a CommandProcessor object. */
    virtual ~CommandProcessor();

    //  Virtual methods
    /** \brief Returns a command from a source.
     *  \param _ Takes a single parameter, a State object signifying the current state.
     *  \return A 'Command' object */
    virtual Command& getCommand(const State&) = 0;

    /** \brief Returns a deep copy of the object. */
    virtual CommandProcessor* clone() const noexcept = 0;

    //  Other methods
    /** \brief Determines if a command is valid given the current state.
     *  \remarks Only tests if the command if it is syntactically valid, which does not guarantee that the command will
     *  be correctly executed. */
    bool validate(const Command&, const State&);



protected:
    //  A vector of states
    std::vector<State> states;

    //  A vector of objects containing the transition data
    std::vector<TransitionData> transitionDatabase;

    /** \brief Returns a collection of help strings (for commands that contain the correct syntax) given the current
     *  state. */
    std::vector<std::string> getHelpStrings(const State&) const;
};



/** \class ConsoleCommandProcessorAdapter
 *  \brief A class that supplies commands from the standard cpp input stream. */
class ConsoleCommandProcessorAdapter : public CommandProcessor {
public:
    //  Constructors/Deconstructor
    /** \brief Constructs a 'default' ConsoleCommandProcessorAdapter object. */
    ConsoleCommandProcessorAdapter();
    /** \brief Constructs a ConsoleCommandProcessorAdapter given a configuration of states and transitions. */
    ConsoleCommandProcessorAdapter(std::vector<State>, std::vector<TransitionData>);
    /** \brief Constructs a ConsoleCommandProcessorAdapter using data from a GameEngine object. */
    explicit ConsoleCommandProcessorAdapter(const GameEngine&);
    /** \brief Deconstructs a ConsoleCommandProcessorAdapter object. */
    ~ConsoleCommandProcessorAdapter() override = default;

    //  Overridden methods
    /** \brief Gets a valid command object given the valid state. */
    Command& getCommand(const State&) override;
    /** \brief Returns a deep copy of the object. */
    ConsoleCommandProcessorAdapter* clone() const noexcept override;
};



/** \class FileCommandProcessorAdapter
 *  \brief A class that supplies commands from a specified file. */
class FileCommandProcessorAdapter : public CommandProcessor {
public:
    //  Constructors/Deconstructors
    /** \brief Constructs a 'default' FileCommandProcessorAdapter object. */
    FileCommandProcessorAdapter();
    /** \brief Constructs a FileCommandProcessorAdapter object from a configuration of states and transition data. */
    FileCommandProcessorAdapter(std::vector<State>, std::vector<TransitionData>, std::string );
    /** \brief Constructs a FileCommandProcessorAdapter given a configuration of states and transitions from a
     * GameObject */
    FileCommandProcessorAdapter(const GameEngine&, std::string );
    /** \brief Deconstructs a FileCommandProcessorAdapter object. */
    ~FileCommandProcessorAdapter() override;

    //  Overridden methods
    /** \brief Gets a valid command object given the valid state. */
    Command& getCommand(const State&) override;
    /** \brief Returns a deep copy of the object. */
    FileCommandProcessorAdapter* clone() const noexcept override;

private:
    //  A queue of commands.
    std::queue<Command> commandQueue;

    //  The path of the file to read from.
    std::string filePath;

    //  A backup command processor. Used to take commands from in the case that the commands from the specified file
    //  have been exhausted / run out.
    ConsoleCommandProcessorAdapter* backupCommandProcessor = nullptr;

    //  Loads the contents from the specified file to the command queue.
    //  THROWS an exception if the specified file could not be found.
    void loadFileContents();
};

#ifdef __GNUC__
#pragma clang diagnostic pop
#endif

#endif  //  COMMAND_PROCESSING_H
