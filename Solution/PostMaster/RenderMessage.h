#pragma once
#include "Message.h"

struct RenderMessage : public Message
{
	RenderMessage();
};

inline RenderMessage::RenderMessage()
	: Message(eMessageType::RENDER)
{
}