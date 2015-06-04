# GNU Make solution makefile autogenerated by Premake

.NOTPARALLEL:

ifndef config
  config=release
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),release)
  lists_config = release
endif
ifeq ($(config),debug)
  lists_config = debug
endif

PROJECTS := lists

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

lists:
ifneq (,$(lists_config))
	@echo "==== Building lists ($(lists_config)) ===="
	@${MAKE} --no-print-directory -C . -f lists.make config=$(lists_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f lists.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  release"
	@echo "  debug"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   lists"
	@echo ""
	@echo "For more information, see http://industriousone.com/premake/quick-start"
