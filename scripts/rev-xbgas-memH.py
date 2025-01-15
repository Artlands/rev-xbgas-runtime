#
# Copyright (C) 2017-2025 Tactical Computing Laboratories, LLC
# All Rights Reserved
# contact@tactcomplabs.com
#
# See LICENSE in the top level directory for licensing details
#
# rev-xbgas-test.py
#

# ---------------------------------------------------------------
#
#  xbgas_host0           xbgas_host1
#      |                     |
#  rmt_mem_ctrl0        rmt_mem_ctrl1    
#      |                     |  
#     nic0                  nic1
#      |                     |
#    iface0 <-> router <-> iface1
#                  |
#               topology
#
#   <-> is a link
#   | is a subcomponent relationship

import os
import sst
import sys

if len(sys.argv) != 2:
  sys.stderr.write("Usage: You must pass the executable you wish to simulate using the '--model-options' option with sst\n")
  raise SystemExit(1)

NPES = 2
VERBOSE = 1
PROGRAM = sys.argv[1]
CLOCK = "2.5GHz"  
MEMSIZE = 1024*1024*1024*2                      # Errors if larger than 4GB
SHARED_MEM_SIZE = 1024*1024*16

CACHE_LINE_SIZE = "64"
L1_CACHE_SIZE = "32KiB"
L2_CACHE_SIZE = "256KiB"

xbgas_cpu_params = {
  "verbose" : VERBOSE,                          # Verbosity
  "clock" : CLOCK,                              # Clock
  "program" : os.getenv("REV_EXE", PROGRAM),    # Target executable
  "memSize" : MEMSIZE,                          # Memory size in bytes
  "startAddr" : "[0:0x00000000]",               # Starting address for core 0
  "machine" : "[0:RV64GC_Xbgas]",
  "memCost" : "[0:1:10]",                       # Memory loads required 1-10 cycles
  "enable_xbgas" : 1,                           # Enable XBGAS support 
  "enableMemH": 1,                              # Enable memHierarchy support
  "shared_memory_size": SHARED_MEM_SIZE,        # Shared memory size
  "splash" : 0                                  # Display the splash message
}

memctrl_params = {
  "clock": "1GHz",
  "addr_range_start": 0,
  "addr_range_end": MEMSIZE-1,
  "backing": "malloc"
}

l1cache_params = {
  "cache_frequency" : CLOCK,
  "cache_size" : L1_CACHE_SIZE,
  "associativity" : "8",
  "cache_line_size" : CACHE_LINE_SIZE,
  "access_latency_cycles" : "4",
  "L1" : "1",
  "replacement_policy" : "lru",
  "coherence_protocol" : "MESI",
  "mshr_latency_cycles": 2,
}

l2cache_params = {
  "cache_frequency" : CLOCK,
  "cache_size" : L2_CACHE_SIZE,
  "associativity" : "16",
  "cache_line_size" : CACHE_LINE_SIZE,
  "access_latency_cycles" : "12",
  "replacement_policy" : "lru",
  "coherence_protocol" : "MESI",
  "mshr_latency_cycles": 8,
}

mem_params = {
  "access_time" : "50ns",
  "mem_size" : "4GB"
}

net_params = {
  "input_buf_size" : "512B",
  "output_buf_size" : "512B",
  "link_bw" : "10GB/s"
}

router_params = {
  "xbar_bw" : "10GB/s",
  "flit_size" : "32B",
  "num_ports" : str(NPES),
  "id" : 0
}

# setup the router
router = sst.Component("router", "merlin.hr_router")
router.setSubComponent("topology", "merlin.singlerouter")
router.addParams(net_params)
router.addParams(router_params)

for i in range(0, NPES):
  # xBGAS CPUs
  xbgas_cpu = sst.Component("cpu" + str(i), "revcpu.RevCPU")
  xbgas_cpu.addParams(xbgas_cpu_params)

  # --- Setup the local memory hierarchy --- #
  # Setup the memory controllers
  lsq = xbgas_cpu.setSubComponent("memory", "revcpu.RevBasicMemCtrl")

  # Create the memHierarchy subcomponent
  miface = lsq.setSubComponent("memIface", "memHierarchy.standardInterface")

  # Create the L1 cache in memHierarchy
  l1cache = sst.Component("l1cache" + str(i), "memHierarchy.Cache")
  l1cache.addParams(l1cache_params)

  # Create the L2 cache in memHierarchy
  l2cache = sst.Component("l2cache" + str(i), "memHierarchy.Cache")
  l2cache.addParams(l2cache_params)
  
  # Create the memory controller in memHierarchy
  memctrl = sst.Component("memory" + str(i), "memHierarchy.MemController")
  memctrl.addParams(memctrl_params)

  # Create the memory backend subcomponent
  memory = memctrl.setSubComponent("backend", "memHierarchy.simpleMem")
  memory.addParams(mem_params)
  
  # CPU to L1 cache link
  link_miface_l1cache = sst.Link("link_miface_l1cache" + str(i))
  link_miface_l1cache.connect((miface, "port", "50ps"), (l1cache, "high_network_0", "50ps"))

  # L1 cache to L2 cache link
  link_l1cache_l2cache = sst.Link("link_l1cache_l2cache" + str(i))
  link_l1cache_l2cache.connect((l1cache, "low_network_0", "100ps"), (l2cache, "high_network_0", "100ps"))

  # L2 cache to memory controller link
  link_l2cache_mem = sst.Link("link_l2cache_mem" + str(i))
  link_l2cache_mem.connect((l2cache, "low_network_0", "150ps"), (memctrl, "direct_link", "150ps"))
  
  # --- Setup the remote memory hierarchy --- #
  # Create remote memory controllers
  rmt_lsq = xbgas_cpu.setSubComponent("remote_memory", "revcpu.RevBasicRmtMemCtrl")
  rmt_nic = rmt_lsq.setSubComponent("xbgasNicIface", "revcpu.XbgasNIC")
  rmt_nic_iface = rmt_nic.setSubComponent("iface", "merlin.linkcontrol")
  rmt_nic_iface.addParams(net_params)

  # Nic to the router
  link_nic_router = sst.Link("link" + str(i))
  link_nic_router.connect( (rmt_nic_iface, "rtr_port", "400ns"), (router, f"port{i}", "400ns") )

# sst.setStatisticLoadLevel(4)
# sst.setStatisticOutput("sst.statOutputCSV")
# sst.enableAllStatisticsForAllComponents()

# EOF
