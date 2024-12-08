#pragma once
#include <ql/graphic/interactive/draw.hpp>
#include <ql/graphic/interactive/init.hpp>
#include <ql/graphic/interactive/post-update.hpp>
#include <ql/graphic/interactive/update.hpp>
#include <ql/graphic/interactive/type.hpp>

#define ql_state_interactive(param) \
	void initializing() override            \
	{                                       \
		this->interactive_init(param);        \
	}                                       \
                                          \
	void updating() override                \
	{                                       \
		this->interactive_update(param);      \
	}                                       \
																					\
	void post_updating() override           \
	{																			  \
		this->interactive_post_update(param); \
	}                                       \
                                          \
	void drawing() override                 \
	{                                       \
		this->interactive_draw(param);        \
	}

#define ql_declare_interactive \
ql::declare_interactive declare_interactive;