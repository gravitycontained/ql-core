#pragma once
#include <ql/graphic/interactive/draw.hpp>
#include <ql/graphic/interactive/init.hpp>
#include <ql/graphic/interactive/update-signal.hpp>
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
	void updating_phase_signal() override   \
	{																			  \
		this->interactive_update_phase_signal(param); \
	}                                       \
                                          \
	void drawing() override                 \
	{                                       \
		this->interactive_draw(param);        \
	}

#define ql_declare_interactive \
ql::declare_interactive declare_interactive;