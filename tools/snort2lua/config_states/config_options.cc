/*
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
 * Copyright (C) 2002-2013 Sourcefire, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 2 as
 * published by the Free Software Foundation.  You may not use, modify or
 * distribute this program under any other version of the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
// config_options.cc author Josh Rosenbaum <jorosenba@cisco.com>

#include <sstream>
#include <vector>

#include "conversion_state.h"
#include "util/converter.h"
#include "util/util.h"
#include "config_states/config_options.h"


namespace config
{


static inline void open_table_add_option(LuaData* ld,
                                            std::string table_name, 
                                            std::string opt_name, 
                                            bool val)
{
    ld->open_table(table_name);
    ld->add_option_to_table(opt_name, val);
    ld->close_table();
}

/*********************************************
 ************  config paf_max ****************
 *********************************************/

static const std::string paf_max = "paf_max";
static const std::string stream_tcp = "stream_tcp";

static const ConvertMap config_paf_max =
{
    paf_max,
    config_int_ctor<&paf_max, &stream_tcp>,
};

const ConvertMap* paf_max_map = &config_paf_max;


/*************************************************
 ********** PCRE_MATCH_LIMIT  ********************
 *************************************************/


static const std::string pcre_match_limit = "pcre_match_limit";
static const std::string detection = "detection";

static const ConvertMap config_pcre_match_limit =
{
    pcre_match_limit,
    config_int_ctor<&pcre_match_limit, &detection>,
};

const ConvertMap* pcre_match_limit_map = &config_pcre_match_limit;



/***********************************************************
 ********** PCRE_MATCH_LIMIT_RECURSION  ********************
 ***********************************************************/

static const std::string pcre_match_limit_recursion = "pcre_match_limit_recursion";


static const ConvertMap config_pcre_match_limit_recursion =
{
    pcre_match_limit_recursion,
    config_int_ctor<&pcre_match_limit_recursion, &detection>,
};

const ConvertMap* pcre_match_limit_recursion_map = &config_pcre_match_limit_recursion;


/***********************************************************
 ****************** FLOWBIT_SIZE ***************************
 ***********************************************************/

//template<const std::string *snort_option, const std::string *lua_name>
//config_int_ctor2<snort_option, lua_name, snort_option>

static const std::string alerts = "alerts";
static const std::string flowbits_size = "flowbits_size";

static const ConvertMap config_flowbit_size =
{
    flowbits_size,
    config_int_ctor<&flowbits_size, &alerts>,
};

const ConvertMap* flowbit_size_map = &config_flowbit_size;


/*********************************************
 *******  Enable GTP *************************
 *********************************************/

static ConversionState* enable_gtp_ctor(Converter* cv, LuaData* ld)
{
    open_table_add_option(ld, "cd_udp", "enable_gtp", true);
    return nullptr;
}

static const ConvertMap config_enable_gtp =
{
    "enable_gtp",
    enable_gtp_ctor,
};

const ConvertMap* enable_gtp_map = &config_enable_gtp;


/*********************************************
 ****************  Snaplen *******************
 *********************************************/

static const std::string snaplen = "snaplen";
static const std::string daq = "daq";

static const ConvertMap config_snaplen =
{
    snaplen,
    config_int_ctor<&snaplen, &daq>,
};

const ConvertMap* snaplen_map = &config_snaplen;


/*********************************************
 ****************  set_gid *******************
 *********************************************/

static const std::string set_gid = "set_gid";
static const std::string process = "process";

static const ConvertMap config_set_gid =
{
    set_gid,
    config_string_ctor<&set_gid, &process>,
};

const ConvertMap* set_gid_map = &config_set_gid;

/*********************************************
 ****************  set_uid *******************
 *********************************************/

static const std::string set_uid = "set_uid";

static const ConvertMap config_set_uid =
{
    set_uid,
    config_string_ctor<&set_uid, &process>,
};

const ConvertMap* set_uid_map = &config_set_uid;


/*********************************************
 ****************  chroot  *******************
 *********************************************/

static const std::string chroot = "chroot";

static const ConvertMap config_chroot =
{
    chroot,
    config_string_ctor<&chroot, &process>,
};

const ConvertMap* chroot_map = &config_chroot;


/*********************************************
 *******  Autogenerate Decoder Rules *********
 *********************************************/

static ConversionState* autogenerate_preprocessor_decoder_rules_ctor(Converter* cv, LuaData* ld)
{
    open_table_add_option(ld, "ips", "enable_builtin_rules", true);
    return nullptr;
}

static const ConvertMap config_autogenerate_decode_rules =
{
    "autogenerate_preprocessor_decoder_rules",
    autogenerate_preprocessor_decoder_rules_ctor,
};

const ConvertMap* autogenerate_decode_rules_map = &config_autogenerate_decode_rules;



#if 0
config alert with interface name
Appends interface name to alert (snort -I).
config alertfile:  <filename>
Sets the alerts output file.
config asn1:  <max-nodes>
Specifies the maximum number of nodes to track when doing ASN1 decoding. See Section 3.5.35 for more infor- mation and examples.
config autogenerate preprocessor decoder rules
￼￼￼
If Snort was configured to enable decoder and preprocessor rules, this option will cause Snort to revert back to its original behavior of alerting if the decoder or preprocessor generates an event.
config bpf file: <filename>
Specifies BPF filters (snort -F).
config checksum drop: <types>
￼
Types of packets to drop if invalid checksums. Values: none, noip, notcp, noicmp, noudp, ip, tcp, udp, icmp or all (only applicable in inline mode and for packets checked per checksum mode config option).
config checksum mode: <types>
￼

See Table 3.2 for a list of classifications.
config cs dir: <path>
￼
configure snort to provide a Unix socket in the path that can be used to issue commands to the running process. See Section 1.10 for more details.
config daemon
Forks as a daemon (snort -D).
config decode data link
Decodes Layer2 headers (snort -e).
config default rule state: <state>
￼￼
Global configuration directive to enable or disable the load- ing of rules into the detection engine. Default (with or without directive) is enabled. Specify disabled to disable loading rules.
config daq:  <type>
Selects the type of DAQ to instantiate. The DAQ with the highest version of the given type is selected if there are multiple of the same type (this includes any built-in DAQs).
config daq mode: <mode>
￼
Select the DAQ mode: passive, inline, or read-file. Not all DAQs support modes. See the DAQ distro README for possible DAQ modes or list DAQ capabilities for a brief summary.
config daq var: <name=value>
￼
Set a DAQ specific variable. Snort just passes this infor- mation down to the DAQ. See the DAQ distro README for possible DAQ variables.
config daq dir: <dir>
￼
Tell Snort where to look for available dynamic DAQ mod- ules. This can be repeated. The selected DAQ will be the one with the latest version.
config daq list: [<dir>]
￼
Tell Snort to dump basic DAQ capabilities and exit. You can optionally specify a directory to include any dynamic DAQs from that directory. You can also precede this op- tion with extra DAQ directory options to look in multiple directories.
config decode esp: [enable | disable]
￼
￼￼￼config disable decode alerts
￼￼￼Turns off the alerts generated by the decode phase of Snort.
￼￼config disable inline init failopen
￼￼￼￼Disables failopen thread that allows inline traffic to pass while Snort is starting up. Only useful if Snort was configured with –enable-inline-init-failopen. (snort --disable-inline-init-failopen)
￼￼config disable ipopt alerts
￼￼￼Disables IP option length validation alerts.
￼￼config disable tcpopt alerts
￼￼￼Disables option length validation alerts.
￼￼config
disable tcpopt experimental alerts
￼￼￼￼Turns off alerts generated by experimental TCP options.
￼￼￼￼config disable tcpopt obsolete alerts Turns off alerts generated by obsolete TCP options.
￼￼￼￼￼￼config disable tcpopt ttcp alerts
￼Turns off alerts generated by T/TCP options.
￼￼￼￼￼config disable ttcp alerts
￼￼￼Turns off alerts generated by T/TCP options.
￼￼config dump chars only
￼Turns on character dumps (snort -C).
￼￼￼￼config dump payload
￼Dumps application layer (snort -d).
￼￼￼config dump payload verbose
￼￼￼Dumps raw packet starting at link layer (snort -X).
￼￼config enable decode drops
￼￼￼Enables the dropping of bad packets identified by decoder (only applicable in inline mode).
￼￼￼￼config enable decode oversized alerts Enable alerting on packets that have headers containing length fields for which the value is greater than the length
￼￼￼of the packet.
￼￼￼￼￼￼￼￼￼￼37
￼￼￼config enable decode oversized drops
￼￼￼￼Enable dropping packets that have headers containing length fields for which the value is greater than the length of the packet. enable decode oversized alerts must also be enabled for this to be effective (only applicable in inline mode).
￼￼￼￼￼config enable deep teredo inspection
￼￼￼￼Snort’s packet decoder only decodes Teredo (IPv6 over UDP over IPv4) traffic on UDP port 3544. This option makes Snort decode Teredo traffic on all UDP ports.
￼￼config enable ipopt drops
￼￼￼Enables the dropping of bad packets with bad/truncated IP options (only applicable in inline mode).
￼￼config enable mpls multicast
￼￼￼Enables support for MPLS multicast. This option is needed when the network allows MPLS multicast traffic. When this option is off and MPLS multicast traffic is de- tected, Snort will generate an alert. By default, it is off.
￼￼config enable mpls overlapping ip
￼￼￼￼Enables support for overlapping IP addresses in an MPLS network. In a normal situation, where there are no over- lapping IP addresses, this configuration option should not be turned on. However, there could be situations where two private networks share the same IP space and differ- ent MPLS labels are used to differentiate traffic from the two VPNs. In such a situation, this configuration option should be turned on. By default, it is off.
￼￼config enable tcpopt drops
￼￼￼Enables the dropping of bad packets with bad/truncated TCP option (only applicable in inline mode).
￼￼config
enable tcpopt experimental drops
￼￼￼￼Enables the dropping of bad packets with experimental TCP option. (only applicable in inline mode).
￼￼config enable tcpopt obsolete drops
￼￼￼￼Enables the dropping of bad packets with obsolete TCP option. (only applicable in inline mode).
￼￼config enable tcpopt ttcp drops
￼￼￼￼Enables the dropping of bad packets with T/TCP option. (only applicable in inline mode).
￼￼config enable ttcp drops
￼￼￼Enables the dropping of bad packets with T/TCP option. (only applicable in inline mode).
￼￼config event filter: memcap <bytes>
￼￼Set global memcap in bytes for thresholding. Default is 1048576 bytes (1 megabyte).
￼￼config event queue: [max queue <num>] [log <num>] [order events <order>]
￼￼￼￼Specifies conditions about Snort’s event queue. You can use the following options:
• max queue <integer> (max events supported)
• log <integer> (number of events to log)
• order events [priority|content length] (how to order events within the queue)
See Section 2.4.4 for more information and examples.
￼￼￼￼￼config flowbits size: <num-bits>
￼￼Specifies the maximum number of flowbit tags that can be used within a rule set. The default is 1024 bits and maximum is 2048.
￼￼config ignore ports: <proto> <port-list>
￼￼Specifies ports to ignore (useful for ignoring noisy NFS traffic). Specify the protocol (TCP, UDP, IP, or ICMP), followed by a list of ports. Port ranges are supported.
￼￼config interface:  <iface>
￼Sets the network interface (snort -i).
￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼38
￼￼￼config ipv6 frag:
[bsd icmp frag alert on|off] [, bad ipv6 frag alert on|off] [, frag timeout <secs>] [,
max frag sessions <max-track>]
￼￼￼￼￼￼￼￼￼￼￼The following options can be used:
• bsd icmp frag alert on|off (Specify whether or not to alert. Default is on)
• bad ipv6 frag alert on|off (Specify whether or not to alert. Default is on)
• frag timeout <integer> (Specify amount of time in seconds to timeout first frag in hash table)
• max frag sessions <integer> (Specify the num- ber of fragments to track in the hash table)
￼￼￼￼￼￼￼￼￼￼￼config logdir:  <dir>
￼Sets the logdir (snort -l).
￼￼config log ipv6 extra data
￼￼￼￼Set Snort to log IPv6 source and destination addresses as unified2 extra data events.
￼￼config max attribute hosts: <hosts>
￼￼￼Sets a limit on the maximum number of hosts to read from the attribute table. Minimum value is 32 and the maxi- mum is 524288 (512k). The default is 10000. If the number of hosts in the attribute table exceeds this value, an error is logged and the remainder of the hosts are ignored. This option is only supported with a Host Attribute Table (see section 2.7).
￼￼￼￼config max attribute services per hostS:ets a per host limit on the maximum number of services to <hosts> read from the attribute table. Minimum value is 1 and the maximum is 65535. The default is 100. For a given host, if the number of services in the attribute table exceeds this value, an error is logged and the remainder of the services for that host are ignored. This option is only supported
with a Host Attribute Table (see section 2.7).
￼￼￼￼￼￼￼config max mpls labelchain len: <num-hdrs>
￼￼￼￼Sets a Snort-wide limit on the number of MPLS headers a packet can have. Its default value is -1, which means that there is no limit on label chain length.
￼￼config min ttl: <ttl>
￼￼Sets a Snort-wide minimum ttl to ignore all traffic.
￼￼config mpls payload type: ipv4|ipv6|ethernet
￼￼￼Sets a Snort-wide MPLS payload type. In addition to ipv4, ipv6 and ethernet are also valid options. The default MPLS payload type is ipv4
￼￼config no promisc
￼￼Disables promiscuous mode (snort -p).
￼￼config nolog
￼Disables logging. Note: Alerts will still occur. (snort -N).
￼￼config nopcre
￼Disables pcre pattern matching.
￼￼config obfuscate
￼Obfuscates IP Addresses (snort -O).
￼￼config order:  <order>
￼Changes the order that rules are evaluated, e.g.: pass alert log activation.
￼￼config pcre match limit: <integer>
￼￼￼Restricts the amount of backtracking a given PCRE op- tion. For example, it will limit the number of nested re- peats within a pattern. A value of -1 allows for unlimited PCRE, up to the PCRE library compiled limit (around 10 million). A value of 0 results in no PCRE evaluation. The snort default value is 1500.
￼￼config pcre match limit recursion: <integer>
￼￼￼￼Restricts the amount of stack used by a given PCRE op- tion. A value of -1 allows for unlimited PCRE, up to the PCRE library compiled limit (around 10 million). A value of 0 results in no PCRE evaluation. The snort default value is 1500. This option is only useful if the value is less than the pcre match limit
￼￼config pkt count: <N>
￼￼￼￼Exits after N packets (snort -n).
￼￼￼￼￼￼￼￼￼￼￼￼￼￼39
￼￼￼config policy version: <base-version-string> [<binding-version-string>]
￼￼Supply versioning information to configuration files. Base version should be a string in all configuration files including included ones. In addition, binding version must be in any file configured with config binding. This option is used to avoid race conditions when modifying and loading a configuration within a short time span - before Snort has had a chance to load a previous configuration.
￼￼config profile preprocs
￼￼Print statistics on preprocessor performance. See Section 2.5.2 for more details.
￼￼config profile rules
￼￼Print statistics on rule performance. See Section 2.5.1 for more details.
￼￼config protected content: md5|sha256|sha512
￼￼Specifies a default algorithm to use for protected content rules.
￼￼￼config quiet
￼Disables banner and status reports (snort -q). NOTE: The command line switch -q takes effect immediately af- ter processing the command line parameters, whereas us- ing config quiet in snort.conf takes effect when the con- figuration line in snort.conf is parsed. That may occur after other configuration settings that result in output to console or syslog.
￼￼config reference:  <ref>
￼Adds a new reference system to Snort, e.g.: myref http://myurl.com/?id=
￼￼config reference net <cidr>
￼￼For IP obfuscation, the obfuscated net will be used if the packet contains an IP address in the reference net. Also used to determine how to set up the logging directory structure for the session post detection rule option and ASCII output plugin - an attempt is made to name the log directories after the IP address that is not in the reference net.
￼￼config response:  [attempts
<count>] [, device <dev>]
￼Set the number of strafing attempts per injected response and/or the device, such as eth0, from which to send re- sponses. These options may appear in any order but must be comma separated. The are intended for passive mode.
￼￼config show year
￼￼Shows year in timestamps (snort -y).
￼￼config so rule memcap: <bytes>
￼￼￼Set global memcap in bytes for so rules that dynamically allocate memory for storing session data in the stream pre- processor. A value of 0 disables the memcap. Default is 0. Maximum value is the maximum value an unsigned 32 bit integer can hold which is 4294967295 or 4GB.
￼￼config stateful
￼Sets assurance mode for stream (stream is established).
￼￼config tagged packet limit: <max-tag>
￼￼￼When a metric other than packets is used in a tag option in a rule, this option sets the maximum number of packets to be tagged regardless of the amount defined by the other metric. See Section 3.7.5 on using the tag option when writing rules for more details. The default value when this option is not configured is 256 packets. Setting this option to a value of 0 will disable the packet limit.
￼￼config threshold:  memcap <bytes>
￼Set global memcap in bytes for thresholding. Default is 1048576 bytes (1 megabyte). (This is deprecated. Use config event filter instead.)
￼￼config umask:  <umask>
￼￼Sets umask when running (snort -m).
￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼￼40
config utc
Uses UTC instead of local time for timestamps (snort -U).
config verbose
Uses verbose logging to STDOUT (snort -v).
config vlan agnostic
￼
Causes Snort to ignore vlan headers for the purposes of connection and frag tracking. This option is only valid in the base configuration when using multiple configurations, and the default is off.
config address space agnostic
￼￼
Causes Snort to ignore DAQ address space ID for the pur- poses of connection and frag tracking. This option is only valid in the base configuration when using multiple config- urations, and the default is off.
config policy mode: tap|inline|inline test
￼
Sets the policy mode to either passive, inline or inline test.
config tunnel verdicts: gtp|teredo|6in4|4in6

#endif

} // namespace config