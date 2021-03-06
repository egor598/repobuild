// Copyright 2013
// Author: Christopher Van Arsdale

#ifndef _REPOBUILD_NODES_ALLNODES_H__
#define _REPOBUILD_NODES_ALLNODES_H__

#include <string>
#include <vector>
#include <map>
#include "common/base/macros.h"
#include "repobuild/nodes/node.h"  // convenience for libraries.

namespace repobuild {

class DistSource;
class Input;
class Makefile;
class TargetInfo;

class NodeBuilder {
 public:
  virtual ~NodeBuilder() {}
  virtual std::string Name() const = 0;
  virtual Node* NewNode(const TargetInfo& target,
                        const Input& input,
                        DistSource* source) = 0;
  virtual void WriteMakeHead(const Input& input, Makefile* out) = 0;
  virtual void FinishMakeFile(const Input& input,
                              const std::vector<const Node*>& all_nodes,
                              DistSource* source,
                              Makefile* out) = 0;

  static void GetAll(std::vector<NodeBuilder*>* nodes);
};

class NodeBuilderSet {
 public:
  NodeBuilderSet();  // uses NodeBuilder::GetAll.
  explicit NodeBuilderSet(const std::vector<NodeBuilder*>& nodes);
  ~NodeBuilderSet();

  // Node generator:
  Node* NewNode(const std::string& name,
                const TargetInfo& target,
                const Input& input,
                DistSource* source) const;

  void WriteMakeHead(const Input& input, Makefile* makefile);
  void FinishMakeFile(const Input& input,
                      const std::vector<const Node*>& nodes,
                      DistSource* source,
                      Makefile* makefile);

 private:
  DISALLOW_COPY_AND_ASSIGN(NodeBuilderSet);

  void Init(const std::vector<NodeBuilder*>& nodes);

  std::vector<NodeBuilder*> all_nodes_;
  std::map<std::string, NodeBuilder*> nodes_;
};

}  // namespace repobuild

# endif  // _REPOBUILD_NODES_ALLNODES_H__
