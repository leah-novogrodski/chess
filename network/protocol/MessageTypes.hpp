#pragma once

namespace protocol {

// One flat enum for both directions, not a ClientMessageType/ServerMessageType
// split: the wire envelope's "type" field is a single string namespace
// regardless of who sent it (see PROTOCOL.md), so a single type -> handler
// lookup table (in whichever later step actually dispatches messages) only
// needs one enum to key off of. Grouped by direction here for readability
// only - the boundary carries no other special meaning.
enum class MessageType {
    // Client -> Server
    Login,
    CreateRoom,
    JoinRoom,
    QuickPlay,
    Click,
    Leave,

    // Server -> Client
    LoginResult,
    RoomJoined,
    MatchmakingResult,
    Snapshot,
    OpponentDisconnected,
    GameOverResult,
    Error,
};

}