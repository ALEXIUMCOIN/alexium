// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>
#include "arith_uint256.h"
#include <fstream>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x7f;
        pchMessageStart[1] = 0x35;
        pchMessageStart[2] = 0x22;
        pchMessageStart[3] = 0x05;
        vAlertPubKey = ParseHex("04e4859569daee357967024a5d0374c10c9921ff3eaa26900118c22778a63694e6db5087be0349c1f84bc4dfcdf624f3fd2b04379c331c1a9541b0bc0e02eaf417");
        nDefaultPort = 45714;
        nRPCPort = 45715;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "Alexium";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1438812711, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1438812711;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 23293;

        if (false)
        {
            ofstream F;
            F.open("1.txt");
            F<<"recalculating params for mainnet.\n";
            for(genesis.nNonce = 1; UintToArith256(bnProofOfWorkLimit.getuint256()) < UintToArith256(genesis.GetHash()); genesis.nNonce++)
            {
                if(genesis.nNonce == 0)
                    genesis.nTime++;
            } 
            F<<"new mainnet genesis merkle root: "<<genesis.hashMerkleRoot.ToString().c_str()<<endl;
            F<<"new mainnet genesis nonce: "<<genesis.nNonce<<endl;
            F<<"new mainnet genesis time: "<<genesis.nTime<<endl;
            F<<"new mainnet genesis hash: "<<genesis.GetHash().ToString().c_str()<<endl;
            F.close();
        }
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00005dbb0c5f9f2e0d34c59365f555cc7cc61842f2ee5d9d9bed4ad0ed6f30ca"));
        assert(genesis.hashMerkleRoot == uint256("0x96b50ffb60828fc4208491f2e42794468e7343261c5502c6a96cac0add249e27"));
/*
        vSeeds.push_back(CDNSSeedData("rat4.alexium.co", "seed.alexium.co"));
        vSeeds.push_back(CDNSSeedData("6.syllabear.us.to", "bcseed.syllabear.us.to"));
*/
        vSeeds.push_back(CDNSSeedData("209.126.77.237", "209.126.77.237"));
        vSeeds.push_back(CDNSSeedData("209.126.76.194", "209.126.76.194"));
        vSeeds.push_back(CDNSSeedData("209.126.76.193", "209.126.76.193"));
        vSeeds.push_back(CDNSSeedData("209.126.75.94", "209.126.75.94"));
        vSeeds.push_back(CDNSSeedData("209.126.74.245", "209.126.74.245"));
        vSeeds.push_back(CDNSSeedData("209.126.69.78", "209.126.69.78"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(23);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(85);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 2391;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("045aeb971044b4a8915e0839317083e666701978b679034f453539a6be492d7949fe056aa5dd663180bec6eae1c569e6c14ee519bb6224ebd673b819742113a387");
        nDefaultPort = 55714;
        nRPCPort = 55715;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 23293;
        if (false)
        {
            ofstream F;
            F.open("2.txt");
            F<<"recalculating params for testnet.\n";
            for(genesis.nNonce = 1; UintToArith256(bnProofOfWorkLimit.getuint256()) < UintToArith256(genesis.GetHash()); genesis.nNonce++)
            {
                if(genesis.nNonce == 0)
                    genesis.nTime++;
            } 
            F<<"new testnet genesis merkle root: "<<genesis.hashMerkleRoot.ToString().c_str()<<endl;
            F<<"new testnet genesis nonce: "<<genesis.nNonce<<endl;
            F<<"new testnet genesis time: "<<genesis.nTime<<endl;
            F<<"new testnet genesis hash: "<<genesis.GetHash().ToString().c_str()<<endl;
            F.close();
        }

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x00005dbb0c5f9f2e0d34c59365f555cc7cc61842f2ee5d9d9bed4ad0ed6f30ca"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xff;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1411111111;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 1;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        if (false)
        {
            ofstream F;
            F.open("3.txt");
            F<<"recalculating params for regtestnet.\n";
            for(genesis.nNonce = 1; UintToArith256(bnProofOfWorkLimit.getuint256()) < UintToArith256(genesis.GetHash()); genesis.nNonce++)
            {
                if(genesis.nNonce == 0)
                    genesis.nTime++;
            } 
            F<<"new regtestnet genesis merkle root: "<<genesis.hashMerkleRoot.ToString().c_str()<<endl;
            F<<"new regtestnet genesis nonce: "<<genesis.nNonce<<endl;
            F<<"new regtestnet genesis time: "<<genesis.nTime<<endl;
            F<<"new regtestnet genesis hash: "<<genesis.GetHash().ToString().c_str()<<endl;
            F.close();
        }

        assert(hashGenesisBlock == uint256("0x5e743d2525c70e339b827b89533cd4143a2e67095980a31b0937d82007b8e420"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
